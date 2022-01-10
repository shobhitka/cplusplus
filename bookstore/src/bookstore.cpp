#include <iostream>
#include <string.h>
#include "bookstore.h"

using namespace std;

Book::Book()
{

}

Book::Book(const char *name, int copies, double price)
{
    strcpy(this->name, name);
    this->copies = copies;
    this->price = price;
}

char *Book::getName()
{
    return name;
}

void Book::updateCopies(int sold)
{
    if (sold > copies) {
        cout << "Selling more than we have ?" << endl;
        return;
    }

    copies = copies - sold;
}

int Book::getCopies()
{
    return copies;
}

double Book::getPrice()
{
    return price;
}

void Book::updatePrice(double newprice)
{
    price = newprice;
}

BookStore::BookStore()
{
    count = 0;
}
void BookStore::addBook(Book &book)
{
    if (count > 16) {
        cout << "Cannot add more books" << endl;
        return;
    }
    books[count] = book;
    count++;
}

Book BookStore::searchBook(const char *title)
{
    Book none("", -1, 0.00); // empty book
    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].getName(), title) == 0) {
            return books[i];
        }
    }
    return none;
}
