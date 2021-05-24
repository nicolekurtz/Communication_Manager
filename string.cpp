#include "string.h"

// Nicole Kurtz
// this class manages an array of characters and operators associated with it

// constructor
String::String()
{
	chars = NULL;
}

// deconstructor
String::~String()
{
	if(chars)
		if(*chars)
			delete [] chars;
	chars = NULL;
}

// copy constructor
String::String(const String & copy): chars(NULL)
{
	chars = new char[strlen(copy.chars) + 1];
	strcpy(chars, copy.chars);
}

// copy constructor
String::String(const String * copy): chars(NULL)
{
	chars = new char[strlen(copy->chars) + 1];
	strcpy(chars, copy->chars);
}
// operator overloading

// setting a string equal to a string object
String & String::operator =(const String & copy)
{
	if(chars)
		if(copy.chars)
			if(*this == copy)
				return *this;
	
	if(chars)
		delete [] chars;

	if(copy.chars)
	{
		chars = new char[strlen(copy.chars) +1];
		strcpy(chars, copy.chars);
	}

	return *this;
}

// setting a string equal to a char *
String & String::operator =(const char * copy)
{
	if(chars)
		if(copy)
			if(*this == copy) return *this;

	if(chars)
		delete [] chars;

	if(copy)
	{
		chars = new char[strlen(copy) + 1];
		strcpy(chars, copy);
	}

	return *this;
}
/*
// setting a string equal to a char *
String & String::operator =(const char copy[])
{
	if(chars)
		if(copy)
			if(*this == copy) return *this;

	if(chars)
		delete [] chars;

	if(copy)
	{
		chars = new char[strlen(copy) + 1];
		strcpy(chars, copy);
	}

	return *this;
}
*/
// adding a string to a string
String String::operator +(const String & copy)
{
	String temp;

	temp += copy;

	return temp;
}

// string info concatinated with char * info
String & String::operator +=(const char * copy)
{
	String temp;
	temp.chars = new char[strlen(chars) + strlen(copy) + 1];
	strcpy(temp.chars, chars);
	strcat(temp.chars, copy);

	chars = temp.chars;

	return *this;
}

// String info concatinated with string info
String & String::operator +=(const String & copy)
{
	String temp(copy);
	temp.chars = new char[strlen(chars) + strlen(copy.chars) + 1];
	strcpy(temp.chars, chars);
	strcat(temp.chars, copy.chars);

	chars = temp.chars;

	return *this;
}

// If current object is less than argument, return true
bool String::operator < (const String& copy)const
{
	if(strcmp(chars, copy.chars) < 0)
		return true;
	return false;
}

// If current object is less than argument, return true
bool String::operator < (const char copy)const
{
	if(*chars < copy)
		return true;
	return false;
}

// If current object is less than argument, return true
bool String::operator > (const char copy)const
{
	if(*chars > copy)
		return true;
	return false;
}

// if current object is greater than argument, return true
bool String::operator > (const String& copy)const
{
	if(strcmp(chars, copy.chars) > 0)
		return true;
	return false;
}

// if current object is great or equal to string argumetn, return true
bool String::operator >=(const String& copy)const
{
	if(strcmp(chars, copy.chars) >= 0)
		return true;
	return false;
}

// if current object is less than or equal to string argument
bool String::operator <=(const String& copy)const
{
	if(strcmp(chars, copy.chars) <= 0)
		return true;
	return false;
}

// if current object is equal to string argument, return true
bool String::operator ==(const String& copy)const
{
	if(strcmp(chars, copy.chars) == 0)
		return true;
	return false;
}

// if current object is equal to character argument, return true
bool String::operator ==(const char * copy)const
{
	if(strcmp(chars, copy) == 0)
		return true;
	return false;
}

// if string is not equal to string argument, return true
bool String::operator !=(const String& copy)const
{
	if(!chars || !copy.chars)
		return false;
		/*
	if(strcmp(*chars, *copy.chars) != 0)
		return true;
		*/
	return !(*this == copy);
}

// if string chars does not exist, reaturn false
bool String::operator !()const
{
	if(!chars)
		return true;
	return false;
}

char & String::operator [] (int index) const
{
	return chars[index];
}

// cout string object info
ostream & operator << (ostream & output, const String& word)
{
	output << word.chars;
	return output;
}

// cout string pointer info
ostream & operator << (ostream & output, const String * word)
{
	output << word->chars;
	return output;
}

// take in info to string object
istream & operator >>(istream & input, String & word)
{
	char temp[100];
	
	input.get(temp, 100, '\n');

	if(!temp) throw;

	if(word.chars)
		delete [] word.chars;
	
	word.chars = new char[strlen(temp) + 1];
	strcpy(word.chars, temp);

	return input;
}

// take in info to string object
istream & operator >>(istream & input, String *& word)
{
	char * temp;
	
	input.get(temp, 100, '\n');

	if(!temp) throw;

	if(word->chars)
		delete [] word->chars;
	
	word->chars = new char[strlen(temp) + 1];
	strcpy(word->chars, temp);

	return input;
}
