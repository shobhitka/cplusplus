#include <iostream>
#include <string>
#include <list>
using namespace std;

#define BOOK_ANY		1
#define BOOK_TECHNICAL	2
#define BOOK_MANAGEMENT	3

class Book {
private:
	string bookTitle;
	double price;

public:
	Book(const string name = "", double price=0.0);
	virtual ~Book();
	string getTitle();
	double getPrice();
	void setPrice(double newPrice);
};

class TechnicalBook : public Book {
	static double discount;
public:
	TechnicalBook(const string title, double cost);
	double getDiscount();
};

class ManagementBook : public Book {
	static double discount;
public:
	ManagementBook(const string title, double cost);
	double getDiscount();
};

class BookDetails {
private:
	Book *b;
	int stock;

public:
	BookDetails(int category, const string bookTitle, double bookCost, int bookStock);
	~BookDetails();
	Book *getBook();
	int getBookStock();
	void setBookStock(int updatedStock);
};

class BookStore {
private:
	string bookStoreName;
	list <BookDetails *> books;
	list <BookDetails *>::iterator bookIter;
	static BookStore *bs;

private:
	BookStore(const string name);
	~BookStore();

public:
	static BookStore *createInstance(const string name);
	static void deleteInstance();
	void addBook(int category, const string bookTitle = "", double bookCost = 0.0, int bookStock = -1);
	void searchBook(const string title, int numCopies);
	BookDetails *searchBook(const string title);
	void displayBooks(int category);
	string getStoreName();
private:
	void _addBook(int category, const string bookTitle, double bookCost, int bookStock);
};