#include "student.h"
#include "string.h"

using namespace std;

void Student::setStudentDetails()
{
    strcpy(name, "Shobhit Kumar");
    marks = 100;
}

void Student::displayStudentDetails()
{
    cout << "Name:" << name << endl;
    cout << "Marks: " << marks << endl;
}