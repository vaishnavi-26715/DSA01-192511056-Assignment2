#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Time {
    int h, m;

public:
    Time(int hh, int mm) : h(hh), m(mm) {}

    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);

    friend inline int minutesBetweenInline(const Time& a, const Time& b);
    friend inline bool earlierInline(const Time& a, const Time& b);

    int minutesTo(const Time& o) const
    {
        int d = (o.h * 60 + o.m) - (h * 60 + m);
        return d < 0 ? -d : d;
    }
    bool isEarlier(const Time& o) const { return h * 60 + m < o.h * 60 + o.m; }

    int getH() const { return h; }
    int getM() const { return m; }
};

__attribute__((noinline)) int minutesBetween(const Time& a, const Time& b)
{
    int d = (b.h * 60 + b.m) - (a.h * 60 + a.m);
    return d < 0 ? -d : d;
}

__attribute__((noinline)) bool earlier(const Time& a, const Time& b)
{
    return a.h * 60 + a.m < b.h * 60 + b.m;
}

inline int minutesBetweenInline(const Time& a, const Time& b)
{
    int d = (b.h * 60 + b.m) - (a.h * 60 + a.m);
    return d < 0 ? -d : d;
}

inline bool earlierInline(const Time& a, const Time& b)
{
    return a.h * 60 + a.m < b.h * 60 + b.m;
}

int main()
{
    int h1, m1, h2, m2;

    cout << "Enter departure time (hour minute): ";
    cin >> h1 >> m1;
    cout << "Enter arrival time (hour minute): ";
    cin >> h2 >> m2;

    Time departure(h1, m1), arrival(h2, m2);

    cout << endl << "=== Part 1 : friend functions ===" << endl;
    cout << "Minutes between : " << minutesBetween(departure, arrival) << endl;
    cout << "Arrival earlier than departure? " << boolalpha << earlier(arrival, departure) << endl;

    cout << endl << "=== Part 2 : correctness tests ===" << endl;
    Time t1(9, 45), t2(13, 10), t3(11, 50), t4(12, 20), t5(8, 30);
    cout << "9:45  and 13:10 -> " << minutesBetween(t1, t2) << " (expected 205)" << endl;
    cout << "11:50 and 12:20 -> " << minutesBetween(t3, t4) << " (expected 30, across noon)" << endl;
    cout << "8:30  and 8:30  -> " << minutesBetween(t5, t5) << " (expected 0, same time)" << endl;
    cout << "8:30 earlier than 8:30? " << earlier(t5, t5) << " (expected false)" << endl;
    cout << "11:50 earlier than 12:20? " << earlier(t3, t4) << " (expected true)" << endl;

    cout << endl << "=== Part 3 : member and getter versions ===" << endl;
    cout << "minutesTo : " << departure.minutesTo(arrival) << endl;
    cout << "isEarlier : " << departure.isEarlier(arrival) << endl;
    cout << "getters   : " << departure.getH() << ":" << departure.getM() << endl;

    cout << endl << "=== Part 4 : timing 10,000,000 calls ===" << endl;
    const int N = 10000000;
    long long sum = 0;

    auto s1 = steady_clock::now();
    for (int i = 0; i < N; i++) {
        Time a(i % 24, i % 60), b((i + 7) % 24, (i * 3) % 60);
        sum += minutesBetween(a, b) + earlier(a, b);
    }
    double tNormal = duration<double, milli>(steady_clock::now() - s1).count();

    auto s2 = steady_clock::now();
    for (int i = 0; i < N; i++) {
        Time a(i % 24, i % 60), b((i + 7) % 24, (i * 3) % 60);
        sum += minutesBetweenInline(a, b) + earlierInline(a, b);
    }
    double tInline = duration<double, milli>(steady_clock::now() - s2).count();

    auto s3 = steady_clock::now();
    for (int i = 0; i < N; i++) {
        Time a(i % 24, i % 60), b((i + 7) % 24, (i * 3) % 60);
        sum += a.minutesTo(b) + a.isEarlier(b);
    }
    double tMember = duration<double, milli>(steady_clock::now() - s3).count();

    cout << "Friend (not inline) : " << tNormal << " ms" << endl;
    cout << "Friend (inline)     : " << tInline << " ms" << endl;
    cout << "Member functions    : " << tMember << " ms" << endl;
    cout << "Check sum           : " << sum << endl;

    return 0;
}