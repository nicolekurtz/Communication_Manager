#include "device.h"
using namespace std;

// Nicole Kurtz

////////* DEVICE FUNCTIONS *///////
// this is the base class of cellphone, landline, email
// This class finds device, change monthly cost, and name
// It has the following data: name, cost


// constructor
device::device(): bill(false)
{
	name = new String;
	description = new String;
	cost = new String;
}

// deconstructor
device::~device()
{
	if(name)
		delete name;
	if(description)
		delete description;
	if(cost)
		delete cost;
}

// device equal to argument cell
device& device::operator = (const device& copy)
{
	if(this == &copy)
		return *this;
/*
	if(name)
		delete name;

	if(description)
		delete description;
	
	if(cost)
		delete cost;
		*/

	name = copy.name;
	description = copy.description;
	cost = copy.cost;

	return *this;
}

// copy constructor
device::device(const device & copy)
{
	name = new String(copy.name);
	description = new String(copy.description);
	cost = new String(copy.cost);
	bill = copy.bill;

}

// copy constructor
device::device(const device *& copy)
{
	name = new String(copy->name);
	description = new String(copy->description);
	cost = new String(copy->cost);
	bill = copy->bill;
}

// add device  -- VIRTUAL FUNCTION
bool device::add_device()
{
	char response;

	cout << endl << endl << "----Create Cellphone----" << endl;
	cout << "What would you like to name this device: ";
	cin >> *name;
	cin.ignore(100, '\n'); 

	cout << "Description: ";
	cin >> *description;
	cin.ignore(100, '\n');

	cout << "Monthly Cost of the phone: ";
	cin >> *cost;
	cin.ignore(100, '\n'); 

	return true;
}

// pay bill -- VIRTUAL FUNCTION 
bool device::pay_bill()
{
	if(bill)
	{
		cout << "Your device, " << name << ", has already been paid this month!" << endl;
		return false;
	}
	else
	{
		bill = true;
		cout << "Your bill of " << cost << "  for " << name << "'s cellphone has been paid in full." << endl;
	}
	return true;
}

// compare passed name to current name of device
bool device::find_device(char * name_compare)
{
	if(*name == name_compare)
		return true;
	return false;
}

// display info about device -- no using this function so it's empty
bool device::display()
{
	if( !name || !description || !cost)
		return false;
	
	cout << "----Device Information----" << endl; 
	if(name)
		cout << "Name: " << *name << endl; 
	if(description)
		cout << "Description: " << *description << endl; 
	if(cost)
		cout << "Cost: " << *cost << endl << endl;

	return true;
}

// change description of device
bool device::change_description()
{
	if(description)
		delete description; 
	
	description = new String;
	cout << endl << "Type the new description of " << name << ": ";
	cin >> *description;
	cin.ignore(100, '\n');

	if(!description)
		return false;

	return true;
}

// change namme of device
bool device::change_name()
{
	if(name)
		delete name;
	
	name = new String;
	cout << endl << "Type the new name for the device: ";
	cin >> *name;
	cin.ignore(100, '\n');

	if(!name)
		return false;

	return true;
}

////// * CELL FUNCTIONS * ////////
// this is a derived class to the base class:device
// this class manages a cellphone, which allows you to 
// pay the bill, change the num, display, and add device
// data members: number

// constructor
cell::cell(): enable_text(false)
{
	number = new String;
}

// deconstructor
cell::~cell()
{
	if(number)
		delete number;
	enable_text = false;
}

// copy constructor
cell::cell(const cell & copy): device(copy)
{
	if(copy.number)
		number = new String(copy.number);
	if(copy.enable_text)
		enable_text = copy.enable_text;
}

// display information about cell phone
bool cell::display()
{
	if(!name || !description)
		return false;
	
	cout << endl <<  "----Cellphone Information----" << endl; 
	if(name)
		cout << "Name: " << *name << endl; 
	if(description)
		cout << "Description: " << *description << endl; 
	if(number)
		cout << "Number: " << *number << endl;
	if(cost)
		cout << "Cost: " << *cost << endl;

	if(enable_text)
		cout << "Text is enabled for this device" << endl << endl;
	else
		cout << "Text is NOT enabled for this device" << endl << endl;

	return true;
}

// pay cell phone bill
bool cell::pay_bill()
{
	if(bill)
	{
		cout << "Your cellphone, " << name << ", has already been paid this month!" << endl;
		return false;
	}
	else
	{
		bill = true;
		cout << "Your bill of " << cost << "  for " << name << "'s cellphone has been paid in full." << endl;
	}
	return true;
}

// add cellphone device
bool cell::add_device()
{
	char response;

	cout << endl << endl << "----Create Cellphone----" << endl;
	cout << "What would you like to name this device: ";
	cin >> *name;
	cin.ignore(100, '\n'); 

	cout << "Description: ";
	cin >> *description;
	cin.ignore(100, '\n');

	cout << "Phone Number: ";
	cin >> *number;
	cin.ignore(100, '\n');

	cout << "Monthly Cost of the phone: ";
	cin >> *cost;
	cin.ignore(100, '\n'); 

	cout << "Would you like to enable texting? Y or N: ";
	cin >> response;
	cin.ignore(100, '\n');
	if(response == 'Y' || response == 'y')
		enable_text = true;
	else
		enable_text = false;

	return true;
}

////// * CELL OPERATOR OVERLOAD * //////

// check to see if cell and argument cell match
bool cell::operator == (const cell& copy)const
{
	// check to make sure there is data in current object
	if(!name || !description || !number || !cost)
		return false;
	
	// check that there is data in argument
	if(!copy.name || !copy.description || !copy.number || !copy.cost)
		return false;
	
	// compare data -- if all matches, return true
	if(name == copy.name)
		if(description == copy.description)
			if(number == copy.number)
				if(cost == copy.cost)
					if(enable_text == copy.enable_text)
						return true;
	return false;
}

// sell cell equal to argument cell
cell& cell::operator = (const cell& copy)
{
	if(*this == copy)
		return *this;

	device::operator=(copy);

	if(number)
		delete number; 

	number = new String(copy.number);
	enable_text = copy.enable_text;

	return *this;
}

// add cell to argument cell
cell cell::operator + (const cell & copy) const
{
	
	// nothing to add, return empty object
	if(!copy.name || !copy.description || !copy.number || !copy.cost)
		if(!name || !description || !number || !cost)
		{
			cell temp;
			return temp;
		}
	
	// current object is empty, only add copy data
	if(!name || !description || !number || !cost)
	{
		cell temp(copy);
		return temp;
	}
	
	// copy object has no data so just set temp object to current object
	if(!copy.name || !copy.description || !copy.number || !copy.cost)
	{
		cell temp;
		temp.name = name;
		temp.description = description;
		temp.number = number;
		temp.cost = cost;
		temp.enable_text = enable_text;

		return temp;
	}
	
	cell temp(copy);

	// copy name info to temp and concatinate 
	*temp.name += *name;

	// copy description info to temp and concatinate 
	*temp.description += *description;

	// copy number info to temp and concatinate 
	*temp.number += *number;

	// copy cost info to temp and concatinate 
	*temp.cost += *cost;

	// copy whether text is enabled
	temp.enable_text = enable_text;

	return temp;
}

// plus equal cell to argument cell
cell& cell::operator += (const cell& copy)
{
	*name += *copy.name;
	*description += *copy.description;
	*number += *copy.number;
	*cost += *copy.cost;
	enable_text = copy.enable_text;

	return *this;
}

// Return specific character of name
String & cell::operator [] (int index) const
{
	return name[index];
}

// Does not equal operator overload
bool cell::operator !=(const cell& copy)const
{
	if(!name && !copy.name)
		return false;

	if(name && !copy.name)
		return true;

	if(!name && copy.name)
		return true;

	if(name->operator!=(*copy.name))
		return true;
	return false;
}

// if cells chars does not exist, reaturn false
bool cell::operator !()const
{
	if(!name)
		return true;
	return false;
}

// less than operator
bool cell::operator < (const cell& cmp)const
{
	if(cmp.name->operator<(name))
		return true;
	return false;
}

// less than operator
bool cell::operator <= (const cell& cmp)const
{
	if(cmp.name->operator<=(name))
		return true;
	return false;
}

// greater than operator
bool cell::operator > (const cell& cmp)const
{
	if(cmp.name->operator>(name))
		return true;
	return false;
}

// greater than operator
bool cell::operator >= (const cell& cmp)const
{
	if(cmp.name->operator>=(name))
		return true;
	return false;
}

// output cell info 
ostream& operator << (ostream& output, const cell& copy)
{
	output << "Name: " << copy.name << endl;
	output << "Description: " << copy.description << endl;
	output << "Number: " << copy.number << endl;
	output << "Cost: " << copy.cost << endl;
	if(copy.enable_text)
		output << "Text Enabled" << endl;
	output << endl;
	return output;
}

// take in info to cell object
istream & operator >>(istream & input, cell & toadd)
{
	toadd.add_device();
	return input;
}


/////* LANDLINE FUNCTIONS */////
// this is a derived class to the base class: device
// this class manages a landline, which allows you to 
// pay the bill, display info, add device, and change number

// constructor
landline::landline(): number(NULL)
{
	number = new String;
}

// deconstructor
landline::~landline()
{
	if(number)
		delete number;
}

// copy constructor
landline::landline(const landline & copy): device(copy)
{

	if(copy.number)
		number = new String(copy.number);
}

// display landline information
bool landline::display()
{
	if(!number || !name || !description || !cost)
		return false;
	
	cout << endl << endl <<   "----Landline Information----" << endl; 
	if(name)
		cout << "Name: " << *name << endl; 
	if(description)
		cout << "Description: " << *description << endl; 
	if(number)
		cout << "Number: " << *number << endl;
	if(cost)
		cout << "Cost: " << *cost << endl << endl;

	return true;
}
/*
// change landline phone number
bool landline::change_number()
{
	if(number)
		delete number; 
	
	
	cout << "Enter your new landline number: ";
	cin >> *number;
	cin.ignore(100, '\n');

	if(!number)
		return false; 

	cout << "Verizon has confirmed that you new number is: " << number << endl;

	return true;
}
*/
// pay landline bill
bool landline::pay_bill()
{
	if(bill)
	{
		cout << "Your landline, " << name << ", has already been paid this month!" << endl;
		return false;
	}
	else
	{
		bill = true;
		cout << "Your bill of " << cost << "  for " << name << "'s landline has been paid in full." << endl;
	}
	return true;
}

// create landline device
bool landline::add_device()
{
	cout << endl << "----Create Landline----" << endl;
	cout << "What would you like to name this device: ";
	cin >> *name;
	cin.ignore(100, '\n'); 

	cout << "Description: ";
	cin >> *description;
	cin.ignore(100, '\n');

	cout << "Phone Number: ";
	cin >> *number;
	cin.ignore(100, '\n');

	cout << "Monthly Cost of the phone: ";
	cin >> *cost;
	cin.ignore(100, '\n'); 

	return true;
}

// landline equal to argument cell
landline& landline::operator = (const landline& copy)
{
	if(this == &copy)
		return *this;
	
	device::operator=(copy);

	if(number)
		delete number;

	number = new String(copy.number);

	return *this;
}

/////* EMAIL FUNCTIONS *///////
// this is the dervice class to the base class: device
// this class manages an email account, which allows you to 
// display info, create email account, and change password

// constructor
email::email(): address(NULL), password(NULL)
{
	address = new String;
	password = new String;
}

// deconstructor
email::~email()
{
	if(address)
		delete address;
	if(password)
		delete password;
}

// copy constructor
email::email(const email & copy): device(copy)
{
	if(copy.address)
		address = new String(copy.address);
	if(copy.password)
		password = new String(copy.password);
}

// display email info
bool email::display()
{
	if(!address || !name || !description || !password)
		return false;
	
	cout << endl << endl << "----Email Information----" << endl; 

	if(name)
		cout << "Name: " << *name << endl; 

	if(description)
		cout << "Description: " << *description << endl; 

	if(address)
		cout << "Email Address: " << *address << endl;

	if(password)
		cout << "Password: " << *password << endl << endl;

	return true;
}
/*
// change password to email
bool email::change_password()
{
	if(password)
		delete password;
	
	cout << "Type the new password: ";
	cin >> *password;

	if(!password)
		return false;
	else
		cout << "Your password has been changed!" << endl;
	
	return true;
}
*/
// create email
bool email::add_device()
{
	cout << endl << "----Create Email----" << endl;
	cout << "What would you like to name this device: ";
	cin >> *name;
	cin.ignore(100, '\n'); 

	cout << "Description: ";
	cin >> *description;
	cin.ignore(100, '\n');

	cout << "Cost: ";
	cin >> *cost;
	cin.ignore(100, '\n');

	cout << "Email Address: ";
	cin >> *address;
	cin.ignore(100, '\n');

	cout << "Password: ";
	cin >> *password;
	cin.ignore(100, '\n');
	
	return true;
}

// pay email bill
bool email::pay_bill()
{
	// check to see if bill has already been paid
	if(bill)
	{
		cout << "Your email, " << name << ", has already been paid this month!" << endl;
		return false;
	}
	else
	{
		bill = true;
		cout << "Your bill of " << cost << "  for " << name << "'s email has been paid in full." << endl;
	}
	return true;
}

// email equal to argument cell
email& email::operator = (const email& copy)
{
	if(this == &copy)
		return *this;
	
	device::operator=(copy);


	if(address)
		delete address;
	if(password)
		delete password;

	address = new String(copy.address);
	password = new String(copy.password);

	return *this;
}
