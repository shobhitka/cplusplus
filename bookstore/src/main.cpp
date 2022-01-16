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

void menu(char *storeName)
{
	cout << "-----------------------------------------" << endl;
	cout << "BookStore: " << storeName << endl;
	cout << "-----------------------------------------" << endl;
	cout << "1. Add new Book" << endl;
	cout << "2. Display all book details" << endl;
	cout << "3. Search book" << endl;
	cout << "4. Exit" << endl;
	cout << "-----------------------------------------" << endl;
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
		int choice;
		menu(store->getStoreName());
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
			case 1:
				store->addBook();
				break;
			case 2:
				store->displayBooks();
				break;
			case 3:
				cout << "Enter title to search: ";
				cin >> title;
				cout << "Enter needed quantities: ";
				cin >> quantity;
				store->searchBook(title, quantity);
				break;
			case 4:
				cout << "Thank you. Bye." << endl;
				BookStore::deleteInstance();
				exit(0);
			default:
				cout << "Invalid choice" << endl;
				break;
		};
	}
}
