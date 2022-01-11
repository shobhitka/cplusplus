#include <iostream>
using namespace std;


class BookStore {
private:
	class Book {
	private:
		char *bookTitle;
		int copies;
		double price;

	public:
		Book(const char *name = "", int copies=-1, double price=0.0);
		~Book();
		char *getTitle();
		void updateCopies(int sold);
		int getCopies();
		void updatePrice(double newprice);
		double getPrice();
	};

	Book *books[16];
	int count = 0;

public:
	BookStore();
	~BookStore();
	void addBook();
	void addBook(const char *name, int copies, double price);
	int searchBook(const char *title);
	int getBookCopies(int index);
	int getBookPrice(int index);
};
