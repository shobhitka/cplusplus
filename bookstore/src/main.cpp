#include <iostream>
#include "bookstore.h"

using namespace std;
int main()
{
	char title[32];
	int quantity;
	BookStore store;

	store.addBook();
	store.addBook();
	store.addBook();

	while (1) {
		cout << "Enter title to search: ";
		cin >> title;
		cout << "Enter needed quantities: ";
		cin >> quantity;

		int id = store.searchBook(title);
		if (id < 0) {
			cout << "Title not available in the store" << endl;
		} else {
			if (store.getBookCopies(id) < quantity) {
				cout << "Book in store, but quantities available: " << store.getBookCopies(id)  << endl;
			} else {
				cout << "Book in store with needed quantities in stock, total cost: Rs " << quantity * store.getBookPrice(id) << endl;
			}
		}
	}
}
