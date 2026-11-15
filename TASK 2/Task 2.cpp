#include <iostream>
#include <vector>
using namespace std;

int& highestMark(int marks[], int n)
{
    int pos = 0;
    for (int i = 1; i < n; i++)
        if (marks[i] > marks[pos]) pos = i;
    return marks[pos];
}

const int& highestMarkConst(const int marks[], int n)
{
    int pos = 0;
    for (int i = 1; i < n; i++)
        if (marks[i] > marks[pos]) pos = i;
    return marks[pos];
}

int highestMarkCopy(const int marks[], int n)
{
    int pos = 0;
    for (int i = 1; i < n; i++)
        if (marks[i] > marks[pos]) pos = i;
    return marks[pos];
}

int highestIndex(const int marks[], int n)
{
    int pos = 0;
    for (int i = 1; i < n; i++)
        if (marks[i] > marks[pos]) pos = i;
    return pos;
}

int* highestPointer(int marks[], int n)
{
    int pos = 0;
    for (int i = 1; i < n; i++)
        if (marks[i] > marks[pos]) pos = i;
    return &marks[pos];
}

int& badMark()
{
    int mark = 80;
    return mark;
}

void printMarks(const int marks[], int n)
{
    for (int i = 0; i < n; i++) cout << marks[i] << ' ';
    cout << endl;
}

int main()
{
    const int n = 6;
    int marks[n];

    cout << "Enter marks of " << n << " students: ";
    for (int i = 0; i < n; i++) cin >> marks[i];

    cout << endl << "Original marks       : ";
    printMarks(marks, n);

    highestMark(marks, n) += 2;
    cout << "After +2 (reference) : ";
    printMarks(marks, n);

    const int& top = highestMarkConst(marks, n);
    cout << "Highest (const ref)  : " << top << endl;

    int copy = highestMarkCopy(marks, n);
    copy += 50;
    cout << "Copy changed to " << copy << ", array still: ";
    printMarks(marks, n);

    marks[highestIndex(marks, n)] += 1;
    cout << "After +1 (index)     : ";
    printMarks(marks, n);

    *highestPointer(marks, n) += 1;
    cout << "After +1 (pointer)   : ";
    printMarks(marks, n);

    cout << endl << "Vector that grows:" << endl;
    vector<int> v;
    v.push_back(56);
    v.push_back(78);
    v.push_back(91);
    int* before = &v[2];
    cout << "capacity before push_back : " << v.capacity() << endl;
    for (int i = 0; i < 10; i++) v.push_back(60 + i);
    int* after = &v[2];
    cout << "capacity after push_back  : " << v.capacity() << endl;
    if (before == after)
        cout << "Same address: old reference still valid" << endl;
    else
        cout << "Address changed: old reference is dangling" << endl;

    return 0;
}