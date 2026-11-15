#include <iostream>
#include <string>
using namespace std;

class Token {
    static int next;
    int id;

public:
    Token() { id = ++next; }
    int get() const { return id; }
    static int issued() { return next - 100; }
};

int Token::next = 100;

class BusTicket {
    static int issued;
    static const int CAPACITY = 3;
    int seat;
    string name;

public:
    explicit BusTicket(const string& n) : seat(0), name(n)
    {
        if (issued < CAPACITY) {
            issued++;
            seat = issued;
        }
    }

    static int count()
    {
        return issued;
    }

    void print() const
    {
        cout << name << ": "
             << (seat ? "Seat " + to_string(seat) : string("Waiting"))
             << '\n';
    }
};

int BusTicket::issued = 0;

void makeTokens()
{
    Token a, b;
    cout << "  inside function: ids " << a.get() << " and " << b.get()
         << ", issued = " << Token::issued() << '\n';
}

int main()
{
    cout << "=== Part 1 : Predict the Output ===" << endl;
    Token counter[3];
    Token extra;
    cout << counter[0].get() << ' ' << counter[2].get() << ' ' << extra.get()
         << ' ' << Token::issued() << '\n';

    cout << endl << "=== Part 2 : Array of BusTicket (4 tickets, 3 seats) ===" << endl;
    BusTicket trip[4] = {BusTicket("Asha"), BusTicket("Bala"),
                         BusTicket("Chitra"), BusTicket("Dev")};
    for (const BusTicket& t : trip) t.print();
    cout << "Issued: " << BusTicket::count() << '\n';

    cout << endl << "=== Part 3 : Objects created inside a function ===" << endl;
    int times;
    cout << "How many times should the function be called? ";
    cin >> times;

    for (int i = 1; i <= times; i++) {
        cout << "Call " << i << ":" << endl;
        makeTokens();
        cout << "  after call, issued = " << Token::issued() << endl;
    }

    return 0;
}