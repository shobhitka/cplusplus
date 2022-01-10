#include <iostream>
#include "prototype.h"
#include "student.h"

#define STUDENT

int main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;

#ifdef PASS
	int i = 12;
	invoke(i);

	std::cout << "Value of i: " << i << std::endl;
#endif
#ifdef FUNC_DEF
    int i, j;
    cout << "Enter valies: ";
    cin >> i >> j;
    add();
    add(i, j);
    add(i, j, 5);
#endif
#ifdef STUDENT
	Student s1;
	s1.setStudentDetails();
	s1.displayStudentDetails();
#endif 
}