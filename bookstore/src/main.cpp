#include <iostream>
#include <signal.h>
#include "bookstore.h"

using namespace std;
static BookStore *store = NULL;

void signal_hanlde(int signum)
{
	(void) signum;
	cout << endl;
	BookStore::deleteInstance();
	exit(0);
}

int main()
{
	char title[32];
	int quantity;

	store = BookStore::createInstance("Gangarams");

	// add signal handler to free book store
	signal(SIGINT, signal_hanlde);

	// Add books directly, though this is overloaded to take user input
	store->addBook("C++", 100.00, 10);
	store->addBook("C", 50.00, 5);
	store->addBook("Java", 200.00, 20);

	while (1) {
		cout << "Enter title to search: ";
		cin >> title;
		cout << "Enter needed quantities: ";
		cin >> quantity;

		store->searchBook(title, quantity);
	}
}
