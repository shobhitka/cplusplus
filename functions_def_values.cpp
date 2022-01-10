#include <iostream>
using namespace std;

#if 0
void add (int a, int b)
{
    cout << "Sum: " << (a + b) << endl;
}

void add (int a, int b, int c)
{
    cout << "Sum: " << (a + b) << endl;
}
#endif

void add (int a = 0, int b = 0, int c = 0)
{
    cout << "Sum: " << (a + b + c) << endl;
}