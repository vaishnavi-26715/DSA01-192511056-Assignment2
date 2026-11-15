#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct Transaction {
    char type;
    int amount;
};

template <int MAX_TXN>
class ShiftAccount {
    int balance;
    Transaction txn[MAX_TXN];
    int count;

public:
    ShiftAccount() : balance(0), count(0) {}

    void add(char type, int amount)
    {
        if (count == MAX_TXN) {
            for (int i = 1; i < MAX_TXN; i++)
                txn[i - 1] = txn[i];
            count--;
        }
        txn[count].type = type;
        txn[count].amount = amount;
        count++;
        balance += (type == 'D') ? amount : -amount;
    }

    int newest(int k) const { return txn[count - 1 - k].amount; }
    int getBalance() const { return balance; }
};

template <int MAX_TXN>
class CircularAccount {
    int balance;
    Transaction txn[MAX_TXN];
    int start;
    int count;

public:
    CircularAccount() : balance(0), start(0), count(0) {}

    void add(char type, int amount)
    {
        if (count == MAX_TXN) {
            txn[start].type = type;
            txn[start].amount = amount;
            start = (start + 1) % MAX_TXN;
        } else {
            int pos = (start + count) % MAX_TXN;
            txn[pos].type = type;
            txn[pos].amount = amount;
            count++;
        }
        balance += (type == 'D') ? amount : -amount;
    }

    int newest(int k) const { return txn[(start + count - 1 - k) % MAX_TXN].amount; }
    int getBalance() const { return balance; }
};

template <int N>
void compare(int ops)
{
    ShiftAccount<N> s;
    CircularAccount<N> c;

    auto t1 = steady_clock::now();
    for (int k = 1; k <= ops; k++)
        s.add(k % 3 == 0 ? 'W' : 'D', k % 1000);
    double ms1 = duration<double, milli>(steady_clock::now() - t1).count();

    auto t2 = steady_clock::now();
    for (int k = 1; k <= ops; k++)
        c.add(k % 3 == 0 ? 'W' : 'D', k % 1000);
    double ms2 = duration<double, milli>(steady_clock::now() - t2).count();

    bool same = (s.getBalance() == c.getBalance());
    for (int k = 0; k < 5; k++)
        if (s.newest(k) != c.newest(k)) same = false;

    cout << "N = " << N << "   shift: " << ms1 << " ms   circular: " << ms2
         << " ms   same result: " << boolalpha << same << endl;
}

int main()
{
    int ops;
    cout << "Enter number of transactions: ";
    cin >> ops;

    cout << endl << "=== Original (shifting) vs Redesigned (circular) ===" << endl;
    compare<10>(ops);
    compare<50>(ops);
    compare<200>(ops);

    return 0;
}