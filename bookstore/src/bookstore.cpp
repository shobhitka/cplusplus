#include <iostream>
#include <string.h>
#include "bookstore.h"

using namespace std;
BookStore *BookStore::bs = NULL;

BookStore::Book::Book(const char *name, double price):bookTitle(new char[strlen(name) + 1])
{
    strcpy(this->bookTitle, name);
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

double BookStore::Book::getPrice()
{
    return price;
}

void BookStore::Book::setPrice(double newprice)
{
    price = newprice;
}

BookStore::BookDetails::BookDetails(const char *bookTitle, double bookCost, int bookStock)
{
    b = new Book(bookTitle, bookCost);
    stock = bookStock;
}

BookStore::BookDetails::~BookDetails()
{
    delete b;
}

BookStore::Book *BookStore::BookDetails::getBook()
{
    return b;
}

int BookStore::BookDetails::getBookStock()
{
    return stock;
}

void BookStore::BookDetails::setBookStock(int updatedStock)
{
    stock = updatedStock;
}

BookStore::BookStore(const char *name):bookStoreName(new char[strlen(name) + 1])
{
    strcpy(bookStoreName, name);
    maxCnt = 5;
}

BookStore::~BookStore()
{
	for (int i = 0; i < bookDetailsCnt; i++)
		delete books[i];

    delete [] bookStoreName;

	cout << "Deleting the store" << endl;
}

BookStore *BookStore::createInstance(const char *name)
{
    if(!bs) {
        bs = new BookStore(name);
    }

    return bs;
}

void BookStore::deleteInstance()
{
    delete bs;
}

void BookStore::_addBook(const char *bookTitle, double bookCost, int bookStock)
{
	BookDetails *bdetails = searchBook(bookTitle);
	if (bdetails) {
		// just update the stock and the price if it has changed
		bdetails->setBookStock(bdetails->getBookStock() + bookStock);
		if (bdetails->getBook()->getPrice() != bookCost) {
			bdetails->getBook()->setPrice(bookCost);
			cout << "Updating price to new price: INR " << bookCost << endl;
		}

		cout << "Update book stock to " << bdetails->getBookStock() << endl;
	} else {
		books[bookDetailsCnt] = new BookDetails(bookTitle, bookCost, bookStock);
		bookDetailsCnt++;
		cout << "Added new book to catalogue" << endl;
	}
}

void BookStore::addBook()
{
	char title[64];
	int copies;
	double price;

    if (bookDetailsCnt == maxCnt) {
        cout << "Cannot add more books" << endl;
        return;
    }

	cout << "Enter book title: ";
	cin >> title;
	cout << "Enter number of copies: ";
	cin >> copies;
	cout << "Enter price: ";
	cin >> price;

	_addBook(title, price, copies);
}

void BookStore::addBook(const char *bookTitle, double bookCost, int bookStock)
{
    if (bookDetailsCnt > maxCnt) {
        cout << "Cannot add more books" << endl;
        return;
    }

	_addBook(bookTitle, bookCost, bookStock);
}

void BookStore::displayBooks()
{
	if (bookDetailsCnt == 0) {
		cout << "Book catalog is empty" << endl;
		return;
	}

	cout << "Title \t\tPrice \t\tStock" << endl;
	cout << "-----------------------------------------" << endl;
	for (int i = 0; i < bookDetailsCnt; i++) {
		cout << books[i]->getBook()->getTitle() << "\t\t" << books[i]->getBook()->getPrice() << "\t\t" << books[i]->getBookStock() << endl;
	}
}

BookStore::BookDetails *BookStore::searchBook(const char *title)
{
    for (int i = 0; i < bookDetailsCnt; i++) {
        if (strcmp(books[i]->getBook()->getTitle(), title) == 0) {
            return books[i];
        }
    }

	return NULL;
}

void BookStore::searchBook(const char *title, int numCopies)
{
	BookDetails *bd = NULL;
    for (int i = 0; i < bookDetailsCnt; i++) {
        if (strcmp(books[i]->getBook()->getTitle(), title) == 0) {
            bd = books[i];
			break;
        }
    }

	if (bd == NULL) {
		// Book not found
		cout << "Book for the specified title does not exist" << endl;
		return;
	}

	if (bd->getBookStock() < numCopies) {
		cout << "Book available but the stock is insufficient." << endl;
		return;
	}

	cout << "Book available with sufficient stock. Total Cost = INR " << bd->getBook()->getPrice() * numCopies << endl;
	return;
}
