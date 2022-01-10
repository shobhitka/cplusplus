#include <iostream>
#include "bookstore.h"

using namespace std;
int main()
{
	char title[32];
	int quantity;
	BookStore store;
	Book b1("C++", 10, 100.00);
	Book b2("C", 5, 200.00);
	Book b3("Java", 20, 300.00);

	store.addBook(b1);
	store.addBook(b2);
	store.addBook(b3);

	cout << "Enter title to search: ";
	cin >> title;
	cout << "Enter needed quantities: ";
	cin >> quantity;

	Book found = store.searchBook(title);
	if (found.getCopies() < 0) {
		cout << "Title not available in the store" << endl;
	} else {
		if (found.getCopies() < quantity) {
			cout << "Book in store, but quantities available: " << found.getCopies() << endl;
		} else {
			cout << "Book in store with needed quantities in stock, total cost: Rs " << quantity * found.getPrice() << endl;
		}
	}
}
