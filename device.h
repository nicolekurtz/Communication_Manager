// Nicole Kurtz
#include "string.h"

// device class object 
// this is the base class of cellphone, landline, email
// This class finds device, change description, and name
class device
{
	public:
		device(); // constructor
		virtual ~device(); // deconstructor
		device(const device *& copy); // copy constructor
		device(const device & copy); // copy constructor
		bool find_device(char * name);  // find device by comparing name
		virtual bool display(); // display info about device
		bool change_description(); // change cost of device
		bool change_name(); // change name of device
		virtual bool add_device(); // create device
		virtual bool pay_bill();  // pay bill

		device& operator = (const device& copy); // overloading equal operator due to dynamic memory

	protected:
		String * name; // name of device
		String * description; // description of device
		String * cost; // cost of cellphone
		bool bill; // bool to track if bill has been paid

	private:
};

// this is a derived class to the base class:device
// this class manages a cellphone, which allows you to 
// pay the bill, change the num, display, and add device
class cell: public device
{
	public:
		cell(); // constructor 
		~cell(); // deconstructor 
		cell(const cell & copy); // copy constructor
		//cell(const cell *& copy); // copy constructor
		bool display(); //display info about cellphone
		bool pay_bill(); // pay cellphone bill
		bool add_device(); // create cellphone object

		// operator overloading functions
		cell& operator = (const cell&); // set cell to argument cell info
		cell operator + (const cell&) const; // add argument cell info to cell
		cell& operator += (const cell&); // plus/equal argument to cell
		String & operator [] (int) const; 
		bool operator == (const cell&)const; // if cells equal eachother return true
		bool operator !=(const cell& copy) const; // if cell does not equal cell
		bool operator !()const; // check if cell exists
		bool operator < (const cell&)const; // less than operator
		bool operator <= (const cell&)const; // less than/equal operator
		bool operator > (const cell&)const; // greater than operator
		bool operator >= (const cell&)const; // greater than/equal operator

		friend ostream& operator << (ostream & output, const cell&); // output object cell info
		friend ostream& operator >> (istream & input, const cell&); // take in cell info

	protected:
		String * number; // phone number
		bool enable_text; // bool of whether text is enabled

	private:
};

// this is a derived class to the base class: device
// this class manages a landline, which allows you to 
// pay the bill, display info, add device, and change number
class landline: public device
{
	public:
		landline(); // constructor 
		~landline(); // deconstructor
		landline(const landline & copy); // copy constructor
		bool display(); // display info about landline
		bool pay_bill(); // pay the landline bill
		bool add_device(); // create landline object
		
		landline& operator = (const landline& copy); // equal operator due to dynamic memory

	protected:
		String * number; // phone number
	private:
};

// this is the dervice class to the base class: device
// this class manages an email account, which allows you to 
// display info, create email account, and change password
class email: public device
{
	public: 
		email(); // constructor
		~email(); // deconstructor
		email(const email & copy); // copy constructor
		bool display(); // display email info
		bool pay_bill(); // pay bill 
		bool add_device(); // create email account


		email& operator = (const email& copy); // equal operator due to dynamic memory
	protected:
		String * address; // email address
		String * password; // password of email account

	private:
};
