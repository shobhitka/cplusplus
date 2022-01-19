#include <iostream>
using namespace std;

class Book {
private:
	char *bookTitle;
	double price;

public:
	Book(const char *name = "", double price=0.0);
	~Book();
	char *getTitle();
	double getPrice();
	void setPrice(double newPrice);
};

class TechnicalBook : public Book {
	static double discount;
	TechnicalBook(const char *title, double cost);
};

class ManagementBook : public Book {
	static double discount;
	ManagementBook(const char *title, double cost);
};

class BookDetails {
private:
	Book *b;
	int stock;

public:
	BookDetails(const char *bookTitle, double bookCost, int bookStock);
	~BookDetails();
	Book *getBook();
	int getBookStock();
	void setBookStock(int updatedStock);
};

class BookStore {
private:
	char *bookStoreName;
	BookDetails *books[16];
	int bookDetailsCnt = 0;
	int maxCnt;
	static BookStore *bs;

private:
	BookStore(const char *name);
	~BookStore();

public:
	static BookStore *createInstance(const char *name);
	static void deleteInstance();
	void addBook(const char *bookTitle = NULL, double bookCost = 0.0, int bookStock = -1);
	void searchBook(const char *title, int numCopies);
	BookDetails *searchBook(const char * title);
	void displayBooks();
	char *getStoreName();
private:
	void _addBook(const char *bookTitle, double bookCost, int bookStock);
};