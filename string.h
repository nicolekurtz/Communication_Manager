// Nicole Kurtz
using namespace std;
#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>


// this class manages an array of characters and operators associated with it
class String
{
	public:
		String(); // constructor
		~String(); // deconstructor
		String(const String &); // copy constructor
		String(const String *); // copy constructor

		// operator overloading
		String & operator =(const String &); // string equals string
		String & operator =(const char *); // string equals char *
		String operator +(const String & copy); // string + string
		String & operator +=(const char * copy); // string info concatinated with char *
		String & operator +=(const String & copy);  // string info concatinated with string
		char & operator [] (int index) const; // subscript operator
		bool operator < (const String&)const; // less than operator
		bool operator < (const char copy)const; // less than operator
		bool operator > (const char copy)const; // less than operator
		bool operator > (const String&)const; // greater than operator
		bool operator >=(const String&)const; // greater than or equal to operator
		bool operator <=(const String&)const; // less than or equal to operator
		bool operator ==(const String&)const; // if data is equal betwen two strings
		bool operator ==(const char *)const;  // if data is equal between string and char *
		bool operator !=(const String&)const; // if data is not equal betwen two strings
		bool operator !()const; // if data does not exist
		friend ostream & operator << (ostream &, const String*); // output string *
		friend ostream & operator << (ostream &, const String&); // output string object
		friend istream & operator >>(istream &, String &); // input string object
		friend istream & operator >>(istream &, String *&); // input string pointer object
	private:
		char * chars; // character array
};

