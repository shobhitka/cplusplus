#include <iostream>
#include "prototype.h"

int main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;

	int i = 12;
	invoke(i);

	std::cout << "Value of i: " << i << std::endl;
}