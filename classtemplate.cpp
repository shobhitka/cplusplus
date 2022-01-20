#include <iostream>
using namespace std;

template<class T1>
class Emp {
    string name;
    T1 sal;
public:
    Emp(string n, T1 s) : name(n), sal(s)
    {}

    virtual void disp();
    virtual ~Emp()
    {}
};

template<class T1, class T2>
class PEmp : public Emp<T1> {
    T2 hra;
public:
    PEmp(string n, T1 s, T2 h) : Emp<T1>(n, s), hra(h)
    {}
    void disp();
};

template<class T1>
void Emp<T1>::disp()
{
    cout << "Name: " << name << ", Salary: " << sal << endl;
}

template<class T1, class T2>
void PEmp<T1, T2>::disp()
{
    Emp<T1>::disp();
    cout << "Hra: " << hra << endl;
}

int main()
{
    Emp<int> e1("Shobhit", 1000);
    e1.disp();

    Emp<double> e2("Shobhit", 2000.50);
    e2.disp();

    Emp<double> *e3 = new PEmp<double, int>("Shobhit", 1000, 450);
    e3->disp();

    delete e3;

    return 0;
}