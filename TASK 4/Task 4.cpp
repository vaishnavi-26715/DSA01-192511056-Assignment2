#include <iostream>
using namespace std;

struct Transaction {
    char type;
    int amount;
};

class SavingsAccount {
private:
    static const int MAX_TXN = 10;
    int accountNo;
    int balance;
    Transaction txn[MAX_TXN];
    int count;

    void record(char type, int amount);

public:
    SavingsAccount(int no, int openingBalance)
    {
        accountNo = no;
        balance = openingBalance;
        count = 0;
    }

    void deposit(int amount);
    bool withdraw(int amount);
    void miniStatement() const;

    int getBalance() const { return balance; }
};

void SavingsAccount::record(char type, int amount)
{
    if (count == MAX_TXN) {
        for (int i = 1; i < MAX_TXN; i++)
            txn[i - 1] = txn[i];
        count--;
    }
    txn[count].type = type;
    txn[count].amount = amount;
    count++;
}

void SavingsAccount::deposit(int amount)
{
    if (amount <= 0) {
        cout << "Invalid amount" << endl;
        return;
    }
    balance += amount;
    record('D', amount);
    cout << "Deposited " << amount << endl;
}

bool SavingsAccount::withdraw(int amount)
{
    if (amount <= 0 || amount > balance) {
        cout << "Withdrawal of " << amount << " refused" << endl;
        return false;
    }
    balance -= amount;
    record('W', amount);
    cout << "Withdrew " << amount << endl;
    return true;
}

void SavingsAccount::miniStatement() const
{
    cout << endl << "Account " << accountNo << " - last " << count << " transactions" << endl;
    for (int i = count - 1; i >= 0; i--)
        cout << "  " << (txn[i].type == 'D' ? "Deposit  " : "Withdraw ") << txn[i].amount << endl;
    cout << "  Balance: " << balance << endl;
}

int main()
{
    int no, opening, choice, amount;

    cout << "Enter account number: ";
    cin >> no;
    cout << "Enter opening balance: ";
    cin >> opening;

    SavingsAccount acc(no, opening);

    do {
        cout << endl << "1. Deposit  2. Withdraw  3. Mini statement  0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter amount: ";
            cin >> amount;
            acc.deposit(amount);
        } else if (choice == 2) {
            cout << "Enter amount: ";
            cin >> amount;
            acc.withdraw(amount);
        } else if (choice == 3) {
            acc.miniStatement();
        }
    } while (choice != 0);

    return 0;
}