#include <iostream>
using namespace std;

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

double charge(double weightKg, bool express = false, bool insured = false)
{
    double total = weightKg * 40;
    if (express) total += 50;
    if (insured) total += 20;
    return total;
}

double charge(int grams)
{
    return charge(grams / 1000.0);
}

double charge(const Parcel& p)
{
    return charge(p.weightKg, p.express, p.insured);
}

int main()
{
    int grams;
    double kg;
    int ex, ins;

    cout << "Enter weight in grams (int): ";
    cin >> grams;
    cout << "Enter weight in kg (double): ";
    cin >> kg;
    cout << "Express delivery? (1 = yes, 0 = no): ";
    cin >> ex;
    cout << "Insurance? (1 = yes, 0 = no): ";
    cin >> ins;

    Parcel p = {kg, ex == 1, ins == 1};

    cout << endl;
    cout << "1. charge(grams)               : Rs " << charge(grams) << endl;
    cout << "2. charge(2)                   : Rs " << charge(2) << "  (int, so 2 grams)" << endl;
    cout << "3. charge(kg)                  : Rs " << charge(kg) << endl;
    cout << "4. charge(2.0f)                : Rs " << charge(2.0f) << "  (float promoted to double)" << endl;
    cout << "5. charge(kg, express)         : Rs " << charge(kg, ex == 1) << endl;
    cout << "6. charge(kg, express, insured): Rs " << charge(kg, ex == 1, ins == 1) << endl;
    cout << "7. charge(parcel)              : Rs " << charge(p) << endl;

    return 0;
}