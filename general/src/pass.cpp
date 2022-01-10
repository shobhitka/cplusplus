#include <iostream>

using namespace std;

#if 0
// pass by value
void invoke(int j)
{
    j++;
}

// pass by address
void invoke(int *j)
{
    (*j)++;
}
#endif

// pass by reference
void invoke(int &j)
{
    j++;
}