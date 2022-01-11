#include <iostream>
using namespace std;

class Book {
private:
	char name[32];
	int copies;
	double price;

public:
	Book(const char *name = "", int copies=-1, double price=0.0);
	char *getName();
	void updateCopies(int sold);
	int getCopies();
	void updatePrice(double newprice);
	double getPrice();
};

class BookStore {
private:
	Book books[16];
	int count = 0;

public:
	BookStore();
	void addBook(Book &book);
	Book searchBook(const char *title);
};
