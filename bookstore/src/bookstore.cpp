#include <iostream>
#include <string.h>
#include <typeinfo>
#include <cxxabi.h>
#include "bookstore.h"

using namespace std;
BookStore *BookStore::bs = NULL;

Book::Book(const string name, double price):bookTitle(name)
{
    this->price = price;
}

Book::~Book()
{
	cout << ">> Deleting Book: " << bookTitle << endl;
}

string Book::getTitle()
{
    return bookTitle;
}

double Book::getPrice()
{
    return price;
}

void Book::setPrice(double newprice)
{
    price = newprice;
}

double TechnicalBook::discount = 5;
TechnicalBook::TechnicalBook(const string title, double cost) : Book(title, cost)
{
}

double ManagementBook::discount = 10;
ManagementBook::ManagementBook(const string title, double cost) : Book(title, cost)
{
}

double TechnicalBook::getDiscount()
{
	return discount;
}

double ManagementBook::getDiscount()
{
	return discount;
}

BookDetails::BookDetails(int category, const string bookTitle, double bookCost, int bookStock)
{
	switch(category) {
		case BOOK_TECHNICAL:
			b = new TechnicalBook(bookTitle, bookCost);
			break;
		case BOOK_MANAGEMENT:
			b = new ManagementBook(bookTitle, bookCost);
			break;
	}

    stock = bookStock;
}

BookDetails::~BookDetails()
{
    delete b;
}

Book *BookDetails::getBook()
{
    return b;
}

int BookDetails::getBookStock()
{
    return stock;
}

void BookDetails::setBookStock(int updatedStock)
{
    stock = updatedStock;
}

BookStore::BookStore(const string name):bookStoreName(name)
{
}

BookStore::~BookStore()
{
	for (bookIter = books.begin(); bookIter != books.end(); bookIter++) {
		delete *bookIter;
	}

	cout << ">> Deleting the store" << endl;
	books.clear();
}

BookStore *BookStore::createInstance(const string name)
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

void BookStore::_addBook(int category, const string bookTitle, double bookCost, int bookStock)
{
	BookDetails *bdetails = searchBook(bookTitle);
	if (bdetails) {
		// just update the stock and the price if it has changed
		bdetails->setBookStock(bdetails->getBookStock() + bookStock);
		if (bdetails->getBook()->getPrice() != bookCost) {
			bdetails->getBook()->setPrice(bookCost);
			cout << ">> Updating price to new price: INR " << bookCost << endl;
		}

		cout << ">> Update book stock to " << bdetails->getBookStock() << endl;
	} else {
		books.push_back(new BookDetails(category, bookTitle, bookCost, bookStock));
		cout << ">> Added new book to catalogue" << endl;
	}
}

void BookStore::addBook(int category, const string bookTitle, double bookCost, int bookStock)
{
	if (bookTitle == "") {
		string title;
		int copies;
		double price;
		cout << "Enter book title: ";
		cin >> title;
		cout << "Enter number of copies: ";
		cin >> copies;
		cout << "Enter price: ";
		cin >> price;

		_addBook(category, title, price, copies);
	} else {
		_addBook(category, bookTitle, bookCost, bookStock);
	}
}

void BookStore::displayBooks(int category)
{
	int displayCnt = 0;
	if (books.empty()) {
		cout << ">> Book catalog is empty" << endl;
		return;
	}

	cout << "Title \t\tPrice \t\tStock \t\tDiscount" << endl;
	cout << "-----------------------------------------------------------" << endl;

	for (bookIter = books.begin(); bookIter != books.end(); bookIter++) {
		BookDetails *bd = *bookIter;
		switch (category) {
		case BOOK_ANY:
			if (typeid(*(bd->getBook())) == typeid(TechnicalBook)) {
				TechnicalBook *b = (TechnicalBook *) bd->getBook();
				cout << b->getTitle() << "\t\t" << b->getPrice() << "\t\t" << bd->getBookStock() << "\t\t" << b->getDiscount() << "%" << endl;
			} else if (typeid(*(bd->getBook())) == typeid(ManagementBook)) {
				ManagementBook *b = (ManagementBook *) bd->getBook();
				cout << b->getTitle() << "\t\t" << b->getPrice() << "\t\t" << bd->getBookStock() << "\t\t" << b->getDiscount() << "%"  << endl;
			}

			displayCnt++;
			break;
		case BOOK_TECHNICAL:
			if (typeid(*(bd->getBook())) == typeid(TechnicalBook)) {
				TechnicalBook *b = (TechnicalBook *) bd->getBook();
				cout << b->getTitle() << "\t\t" << b->getPrice() << "\t\t" << bd->getBookStock() << "\t\t" << b->getDiscount() << "%" << endl;
				displayCnt++;
			}
			break;
		case BOOK_MANAGEMENT:
			if (typeid(*(bd->getBook())) == typeid(ManagementBook)) {
				ManagementBook *b = (ManagementBook *) bd->getBook();
				cout << b->getTitle() << "\t\t" << b->getPrice() << "\t\t" << bd->getBookStock() << "\t\t" << b->getDiscount() << "%" << endl;
				displayCnt++;
			}
			break;
		}
	}

	if (displayCnt == 0) {
		cout << ">> No books in category" << endl;
	}
}

BookDetails *BookStore::searchBook(const string title)
{
    for (bookIter = books.begin(); bookIter != books.end(); bookIter++) {
        if ((*bookIter)->getBook()->getTitle() == title) {
            return *bookIter;
        }
    }

	return NULL;
}

void BookStore::searchBook(const string title, int numCopies)
{
	char ans;
	BookDetails *bd = NULL;
	int discount = 0;
	double price = 0.0;
     for (bookIter = books.begin(); bookIter != books.end(); bookIter++) {
        if ((*bookIter)->getBook()->getTitle() == title) {
            bd = *bookIter;
			break;
        }
    }

	if (bd == NULL) {
		// Book not found
		cout << ">> Book for the specified title does not exist" << endl;
		return;
	}

	if (bd->getBookStock() < numCopies) {
		cout << ">> Book available but the stock is insufficient." << endl;
		return;
	}

	if (typeid(*(bd->getBook())) == typeid(TechnicalBook)) {
		TechnicalBook *b = (TechnicalBook *) bd->getBook();
		discount = b->getDiscount();
		price = b->getPrice() * numCopies * (100 - discount)/100;
	} else {
		ManagementBook *b = (ManagementBook *) bd->getBook();
		discount = b->getDiscount();
		price = b->getPrice() * numCopies * (100 - discount)/100;
	}
	cout << ">> Book available with sufficient stock. Total Cost = INR " << price << " with discount of " << discount << "%" << endl;
	cout << ">> Want to purchase the book (y/n) ? ";
	cin >> ans;
	switch (ans) {
		case 'y':
			// reduce the stock of the book and if stock becomes 0 then delete the book;
			if ((bd->getBookStock() - numCopies) == 0) {
				// Delete the book from the catalogue
				delete bd;
				books.erase(bookIter);
			} else {
				// just update the stock
				bd->setBookStock(bd->getBookStock() - numCopies);
			}

			break;
		case 'n':
			break;
		default:
			cout << ">> Wrong option. Cancelling purchase" << endl;
			break;
	}

	return;
}

string BookStore::getStoreName()
{
	return bookStoreName;
}
