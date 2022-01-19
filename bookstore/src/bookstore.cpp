#include <iostream>
#include <string.h>
#include "bookstore.h"

using namespace std;
BookStore *BookStore::bs = NULL;

Book::Book(const char *name, double price):bookTitle(new char[strlen(name) + 1])
{
    strcpy(this->bookTitle, name);
    this->price = price;
}

Book::~Book()
{
	cout << ">> Deleting Book: " << bookTitle << endl;
	delete [] bookTitle;
}

char *Book::getTitle()
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

double TechnicalBook::discount = 0.05;
TechnicalBook::TechnicalBook(const char *title, double cost) : Book(title, cost)
{
}

double ManagementBook::discount = 0.10;
ManagementBook::ManagementBook(const char *title, double cost) : Book(title, cost)
{
}

BookDetails::BookDetails(const char *bookTitle, double bookCost, int bookStock)
{
    b = new Book(bookTitle, bookCost);
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

	cout << ">> Deleting the store" << endl;
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
			cout << ">> Updating price to new price: INR " << bookCost << endl;
		}

		cout << ">> Update book stock to " << bdetails->getBookStock() << endl;
	} else {
		books[bookDetailsCnt] = new BookDetails(bookTitle, bookCost, bookStock);
		bookDetailsCnt++;
		cout << ">> Added new book to catalogue" << endl;
	}
}

void BookStore::addBook(const char *bookTitle, double bookCost, int bookStock)
{
    if (bookDetailsCnt > maxCnt) {
        cout << ">> Cannot add more books" << endl;
        return;
    }

	if (bookTitle == NULL) {
		char title[64];
		int copies;
		double price;
		cout << "Enter book title: ";
		cin >> title;
		cout << "Enter number of copies: ";
		cin >> copies;
		cout << "Enter price: ";
		cin >> price;

		_addBook(title, price, copies);
	} else {
		_addBook(bookTitle, bookCost, bookStock);
	}
}

void BookStore::displayBooks()
{
	if (bookDetailsCnt == 0) {
		cout << ">> Book catalog is empty" << endl;
		return;
	}

	cout << "Title \t\tPrice \t\tStock" << endl;
	cout << "-----------------------------------------" << endl;
	for (int i = 0; i < bookDetailsCnt; i++) {
		cout << books[i]->getBook()->getTitle() << "\t\t" << books[i]->getBook()->getPrice() << "\t\t" << books[i]->getBookStock() << endl;
	}
}

BookDetails *BookStore::searchBook(const char *title)
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
	char ans;
	BookDetails *bd = NULL;
	int index = -1;
    for (int i = 0; i < bookDetailsCnt; i++) {
        if (strcmp(books[i]->getBook()->getTitle(), title) == 0) {
            bd = books[i];
			index = i;
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

	cout << ">> Book available with sufficient stock. Total Cost = INR " << bd->getBook()->getPrice() * numCopies << endl;
	cout << ">> Want to purchase the book (y/n) ? ";
	cin >> ans;
	switch (ans) {
		case 'y':
			// reduce the stock of the book and if stock becomes 0 then delete the book;
			if ((bd->getBookStock() - numCopies) == 0) {
				// Delete the book from the catalogue
				if (index == (bookDetailsCnt - 1)) {
					// do nothing last book in catalogue
					delete bd;
					bookDetailsCnt--;
				} else {
					//swap the last bookdetail to this index
					books[index] = books[bookDetailsCnt - 1];
					bookDetailsCnt--;
					delete bd;
				}
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

char *BookStore::getStoreName()
{
	return bookStoreName;
}
