#include <iostream>
#include <signal.h>
#include "bookstore.h"

using namespace std;

static BookStore *store = NULL;

void signal_hanlde(int signum)
{
	(void) signum;
	cout << endl;
	delete store;
	exit(0);
}

int main()
{
	char title[32];
	int quantity;

	store = new BookStore();

	// add signal handler to free book store
	signal(SIGINT, signal_hanlde);

	// Add books directly, though this is overloaded to take user input
	store->addBook("C++", 10, 100.00);
	store->addBook("C", 5, 50.00);
	store->addBook("Java", 20, 200.00);

	while (1) {
		cout << "Enter title to search: ";
		cin >> title;
		cout << "Enter needed quantities: ";
		cin >> quantity;

		int id = store->searchBook(title);
		if (id < 0) {
			cout << "Title not available in the store" << endl;
		} else {
			if (store->getBookCopies(id) < quantity) {
				cout << "Book in store, but quantities available: " << store->getBookCopies(id)  << endl;
			} else {
				cout << "Book in store with needed quantities in stock, total cost: Rs " << quantity * store->getBookPrice(id) << endl;
			}
		}
	}
}
