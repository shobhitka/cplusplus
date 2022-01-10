#pragma once
#include <iostream>
using namespace std;

class Student
{
private:
    char name[32];
    int marks;

public:
    void setStudentDetails();
    void displayStudentDetails();
};