#include "contact.h"
using namespace std;

// Nicole Kurtz
// the purpose of this file is to perform functions of a client program
// for means of testing

// prototype
void create_cell(table & contact_list);  // create device
void create_landline(table & contact_list); // create a landline ptr
void create_email(table & contact_list); // create email pointer
void create_contact(table & contact_list); // create contact 
void display_contact(); // display contact information
void display_all_contacts(table & contact_list); // display all contacts in BST
void access_contact(table &contact_list); // access contact from contact list
bool add_device(table & contact_list); // add device to contact
void menu(table & contact_list, int & response); // menu
void remove_contact(table & contact_list); // remove contact from BST
void pay_device(table & contact_list); // pay for device
void submenu(table & contact_list); // access submenu of device
void remove_all(table & contact_list); // remove all contacts
void remove_devices(table & contact_list); // remove all devices from a contact

int main()
{
	table contact_list; // hold my BST of contacts
	int response; // response to menu

	do
	{
	menu(contact_list, response);
	}while(response != 9);

	return 0;
}

// menu to access object
void menu(table & contact_list, int & response)
{

	cout << endl << "---MENU---" << endl;
	cout << "1 - Create Contact" << endl;
	cout << "2 - Display All Contacts & Respective Devices" << endl; 
	cout << "3 - Add Device" << endl;
	cout << "4 - Display a Contact" << endl;
	cout << "5 - Remove Contact" << endl;
	cout << "6 - Access Device Submenu (change name, description, pay bill, etc)" << endl;
	cout << "7 - Remove All Contacts" << endl;
	cout << "8 - Remove All Devices of a Contact" << endl;
	cout << "9 - End Program" << endl;

	cout << "Enter Menu Choice: ";
	cin >> response;
	cin.ignore(100, '\n');

	switch(response)
	{
		case 1:
			create_contact(contact_list);
			break;
		case 2:
			display_all_contacts(contact_list);
			break;
		case 3:
			add_device(contact_list);
			break;

		case 4:
			access_contact(contact_list);
			break;

		case 5:
			remove_contact(contact_list);
			break;

		case 6:
			submenu(contact_list);
			break;

		case 7:
			remove_all(contact_list);
			break;
		
		case 8:
			remove_devices(contact_list);
			break;

		case 9:
			cout << endl << "Thanks for using the Device Management App!" << endl;
			break;
			
	}

}

// remove all devices from a contact
void remove_devices(table & contact_list)
{
	char name_toget[100];
	
	// get name of contact
	cout << endl << "---REMOVE ALL DEVICES---" << endl;

	cout << "Enter name of Contact: ";
	cin.get(name_toget, 100, '\n');
	cin.ignore(100, '\n');

	if(contact_list.remove_devices(name_toget))
		cout << "Devices removed!" << endl;
	else
		cout << "Devices were unable to be removed from that contact" << endl;
}
// delete all contacts in contact list BST
void remove_all(table & contact_list)
{
	cout << endl << "---REMOVE ALL CONTACTS---" << endl;
	if(contact_list.delete_table())
		cout << "Contact list has been deleted!" << endl;
	else
		cout << "There were no contacts to delete. Try entering a contact!" << endl;

}

// access the submenu of the contact list
void submenu(table & contact_list)
{
	char name_toget[100];
	int response;
	
	// get name of contact
	cout << endl << "Enter name of Contact: ";
	cin.get(name_toget, 100, '\n');
	cin.ignore(100, '\n');
	
	do{
	contact_list.submenu(name_toget, response);
	}while(response != 5);
}

// display all contacts in BST
void display_all_contacts(table& contact_list)
{
	cout << endl << "---DISPLAY ALL CONTACTS---" << endl;
	if(!(contact_list.display_all_contacts()))
		cout << "The list of contacts is empty!" << endl;
		
}

// display a specific content
void access_contact(table & contact_list)
{
	cout << endl << "---DISPLAY A CONTACT---" << endl;
	char name_toget[100];
	cout << endl << "Enter name of Contact: ";
	cin.get(name_toget, 100, '\n');
	cin.ignore(100, '\n');
	
	if(!(contact_list.display_contact(name_toget)))
		cout << "Contact can't be found!" << endl;
}

// add a device to a contact
bool add_device(table & contact_list)
{
	int response; 

	cout << endl << "---ADD DEVICE---" << endl;
	cout << endl <<  "--Create Communication Device--" <<endl;
	cout << "1 - Cell Phone" << endl;
	cout << "2 - Landline" << endl;
	cout << "3 - Email" << endl;

	cout << "Type the number of the device you would like to create: ";
	cin >> response;
	cin.ignore(100, '\n');
	
	switch(response)
	{
		case 1:
			create_cell(contact_list);
			break;
		case 2:
			create_landline(contact_list);
			break;
		case 3:
			create_email(contact_list);
			break;
	}

	return false;
}

// create contact
void create_contact(table & contact_list)
{
	char name_toadd[100];
	contact my_contact;

	cout << endl << "----Create Contact----" << endl;
	cout << "Type the name of the contact: ";
	cin.get(name_toadd, 100, '\n');
	cin.ignore(100, '\n');


	if(my_contact.add_contact(name_toadd))
		cout << "Contact Added!" << endl;
	else
		cout << "Contact Not Added" << endl;

	if(contact_list.add_contact(my_contact))
		cout << "Contact added to BST!" << endl;
	else
		cout << "Contact not added to BST" << endl;

	contact_list.display_all_contacts();

}

// remove contact from BST
void remove_contact(table & contact_list)
{
	char name_toget[100];
	cout << endl << "Enter name of Contact to delete: ";
	cin.get(name_toget, 100, '\n');
	cin.ignore(100, '\n');
	
	// function call to remove contact
	if(contact_list.remove_contact(name_toget))
		cout << "Contact removed!"<< endl;
	else
		cout << "Contact not removed" << endl;
}

// create a pointer to a cellphone
void create_cell(table & contact_list)
{
	char name_toget[100];
	cout << endl << "Enter name of Contact: ";
	cin.get(name_toget, 100, '\n');
	cin.ignore(100, '\n');
	
	// create cellphone object
	// dynamic binding
	device * cellphone = new cell;
	cellphone->add_device();
	cellphone->display();
	
	// add to contact
	if(contact_list.add_device(cellphone, name_toget))
		cout << "Device added!" << endl;
	else
		cout << "Device no added." << endl;
	
	if(cellphone)
		delete cellphone;

}

// create a pointer to a email
void create_email(table & contact_list)
{
	char name_toget[100];
	cout << endl << "Enter name of Contact: ";
	cin.get(name_toget, 100, '\n');
	cin.ignore(100, '\n');
	
	// create email object
	// dynamic binding
	device * emails = new email;
	emails->add_device();
	emails->display();

	if(contact_list.add_device(emails, name_toget))
		cout << "Device added!" << endl;
	else
		cout << "Device no added." << endl;
	if(emails)
		delete emails;
}

// create a ptr to a landline object
void create_landline(table & contact_list)
{
	char name_toget[100];
	cout << endl << "Enter name of Contact: ";
	cin.get(name_toget, 100, '\n');
	cin.ignore(100, '\n');
	
	// create landline object
	//dynamic binding
	device * land = new landline;
	land->add_device();
	land->display();

	if(contact_list.add_device(land, name_toget))
		cout << "Device added!" << endl;
	else
		cout << "Device no added." << endl;

	if(land)
		delete land;
}
