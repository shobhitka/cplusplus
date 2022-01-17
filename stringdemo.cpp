#include <iostream>
#include <string.h>

using namespace std;

class StringDemo {
    char *str;

public:
    StringDemo(const char *s = "Hello"):str(new char[strlen(s) + 1])
    {
        strcpy(str, s);
    }

    StringDemo(const StringDemo &newStr):str(new char[strlen(newStr.str) + 1])
    {
        strcpy(str, newStr.str);
    }

    ~StringDemo()
    {
		if (str) {
			delete [] str;
			str = NULL;
		}
    }

    friend ostream &operator<<(ostream &cout, const StringDemo &s);
    friend StringDemo operator+(char *str, const StringDemo &s);

    void operator=(const StringDemo &s)
    {
        delete [] this->str;
        this->str = new char[strlen(s.str) + 1];
        strcpy(this->str, s.str);
    }

    StringDemo operator+(const StringDemo &s)
    {
        char *data;
        int length = strlen(this->str) + strlen(s.str) + 1;
        data = new char[length];
        strcpy(data, this->str);
        strcat(data, s.str);

        StringDemo concat(data);
        delete [] data;
        return concat;
    }

    void operator+=(const char *str)
    {
        char *data = new char[strlen(this->str) + 1];
        strcpy(data, this->str);
        delete [] this->str;
        this->str = new char[strlen(data) + strlen(str) + 1];
        strcpy(this->str, data);
        strcat(this->str, str);
    }

    bool operator==(StringDemo &s)
    {
        if (strcmp(this->str, s.str) == 0)
            return true;
        else
            return false;
    }

    char operator[](int index)
    {
        return this->str[index];
    }

    StringDemo operator()(int sindex, int eindex)
    {
        char *data = new char[eindex - sindex + 1];
        strncpy(data, &this->str[sindex], eindex - sindex + 1);
        StringDemo result(data);
        delete [] data;
        return result;
    }
};

ostream &operator<<(ostream &cout, const StringDemo &s)
{
    cout << s.str;
    return cout;
}

StringDemo operator+(char *str, const StringDemo &s)
{
    strcat(str, s.str);
    StringDemo added(str);
    return added;
}

int main()
{
    StringDemo s1;
    StringDemo s2("World");
    StringDemo s3(s2);

    StringDemo s4 = s1 + s2;

    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s4 = " << s4 << endl;

    s4 += "Program";
    cout << "s4 = " << s4 << endl;

    if (s1 == s2) {
        cout << "Strings s1 and s2 are same" << endl;
    } else {
        cout << "String s1 and s2 are different" << endl;
    }

    if (s2 == s3) {
        cout << "Strings s2 and s3 are same" << endl;
    } else {
        cout << "String s2 and s3 are different" << endl;
    }

    StringDemo s5("Oriented");
    char ch[50];
    strcpy(ch, "Object");

    s5 = ch + s5;
    cout << "s5 = " << s5 << endl;

    cout << "s5[5] = " << s5[5] << endl;

    cout << "s5(2, 5) = " << s5 (2, 5) << endl;

    return 0;
}
