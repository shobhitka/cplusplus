#include <iostream>>

using namespace std;
/*
// keep overloading ..... ?
// not scalable approach
void add (int a, int b)
{
    cout << (a + b) << endl;
}

void add (double a, double b)
{
    cout << (a + b) << endl;
}

void add (int a, double b)
{
    cout << (a + b) << endl;
}
*/
// Use templates
// typename or class as keyword are interchangeable
template<typename T1, typename T2>
void add (T1 a, T2 b)
{
    cout << (a + b) << endl;
}

// if we want return type then?
template<typename T3, typename T1, typename T2>
T3 add(T1 a, T2 b)
{
    return (a+b);
}

template<typename T1>
void invoke()
{
    T1 a = 97;
    a++;
    cout << a << endl;
}

int main()
{
    int i = 2, j = 3;
    add(2,3);
    add(2.1, 3.1); // truncation can happen, not acceptable
    add(2, 4.5); // now what happend ?
    add<string, string>("shobhit", "kumar");
    cout << add<double>(4, 5.5) << endl;

    invoke<int>();
    invoke<char>();
    return 0;
}