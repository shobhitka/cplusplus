#include <iostream>
#include <string.h>
#include "bookstore.h"

using namespace std;

BookStore::Book::Book(const char *name, int copies, double price):bookTitle(new char[strlen(name) + 1])
{
    strcpy(this->bookTitle, name);
    this->copies = copies;
    this->price = price;
}

BookStore::Book::~Book()
{
	cout << "Deleting Book: " << bookTitle << endl;
	delete [] bookTitle;
}

char *BookStore::Book::getTitle()
{
    return bookTitle;
}

void BookStore::Book::updateCopies(int sold)
{
    if (sold > copies) {
        cout << "Selling more than we have ?" << endl;
        return;
    }

    copies = copies - sold;
}

int BookStore::Book::getCopies()
{
    return copies;
}

double BookStore::Book::getPrice()
{
    return price;
}

void BookStore::Book::updatePrice(double newprice)
{
    price = newprice;
}

BookStore::BookStore()
{
    count = 0;
}

BookStore::~BookStore()
{
	for (int i = 0; i < count; i++)
		delete books[i];
}

void BookStore::addBook()
{
	char title[64];
	int copies;
	double price;

    if (count > 16) {
        cout << "Cannot add more books" << endl;
        return;
    }

	cout << "Enter book title: ";
	cin >> title;
	cout << "Enter number of copies: ";
	cin >> copies;
	cout << "Enter price: ";
	cin >> price;

    books[count] = new Book(title, copies, price);
    count++;
}

int BookStore::searchBook(const char *title)
{
    for (int i = 0; i < count; i++) {
        if (strcmp(books[i]->getTitle(), title) == 0) {
            return i;
        }
    }
    return -1;
}

int BookStore::getBookCopies(int index)
{
	if (index > count || index < 0) {
		cout << "Invalid book id: " << index << endl;
		return -1;
	}

	return books[index]->getCopies();
}

int BookStore::getBookPrice(int index)
{
	if (index > count || index < 0) {
		cout << "Invalid book id: " << index << endl;
		return -1;
	}

	return books[index]->getPrice();
}
