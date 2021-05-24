#include "contact.h"
// Nicole Kurtz

/////* CONTACT FUNCTIONS */////

// this class manages a class object that contains a dynamic character name.
// It has a linear linked list of device

// constructor
contact::contact(): name(NULL)
{
	name = new String;
	device_list = new list;
}

// deconstructor
contact::~contact()
{
	if(name)
		delete name;
	if(device_list)
		delete device_list;
}

// copy constructor
contact::contact(const contact & copy)
{
	if(copy.name)
		name = new String(copy.name);
	if(copy.device_list)
		device_list = new list(*copy.device_list);
}

// contact equal to argument contact
contact& contact::operator = (const contact& copy)
{
	if(this == &copy)
		return *this;
	
	if(name)
		delete name;
	
	if(device_list)
		delete device_list;

	name = new String(copy.name);
	device_list = new list(*copy.device_list);
	
	return *this;
}
// add contact
bool contact::add_contact(char * name_toadd)
{
	*name = name_toadd;
	// check that information worked
	if(name)
		return true;
	return false;
}

// display contact information
bool contact::display()
{
	// check that there's information to show
	if(!(*name))
		return false;

	cout << endl << "Contact Information" << endl;
	cout << "Name: " << name << endl;

	return true;
}

//display the content of the device LLL
bool contact::display_list()
{
	if(device_list->display())
		return true;
	return false;
}

// compare contact name to passed name
//contact & contact::find_contact(char * name_tocmp)
bool contact::find_contact(char * name_tocmp)
{
	if(*name == name_tocmp)
	{
		return true;
	}
	return false;
}

// add device to contact
bool contact::add_device(device *& copy)
{
	if(device_list->add_device(copy))
		return true;
	return false;
}

// compare contact names
bool contact::compare_name(contact & cmp)
{
	if(*name > *cmp.name)
		return true;
	return false;
}

// compare contact names
bool contact::compare_name(char * cmp)
{
	if(*name > *cmp)
		return true;
	return false;
}

// remove devices from a contact
bool contact::remove_devices()
{
	if(device_list->remove_devices())
		return true;
	return false;
}

// access device submenu of contact
void contact::submenu(int & response)
{
	char toget[100];
	bool check = false;
	char answer;
	
	// get name of device to work with in contact
	do
	{
		// device could not be found so check to see if user wants to try again
		if(check)
		{
			cout << "The device could not be found, would you like to retype the device name? Y/N: ";
			cin >> answer;
			cin.ignore(100, '\n');
			if(answer == 'N' || answer == 'n')
			{
				response = 5;
				return;
			}
		}

	cout << "What is the name of the device: " << endl;
	cin.get(toget, 100, '\n');
	cin.ignore(100, '\n');
	check = true;
	}while(!(device_list->find_device(toget)));
	
	// pointer to device 
	device * ptr = device_list->return_device(toget);
	
	// loop for submenu
	do
	{

		cout << endl << "---CONTACT SUBMENU---";
		cout << endl << "1 - Change Name";
		cout << endl << "2 - Change Description";
		cout << endl << "3 - Pay Bill";
		cout << endl << "4 - Display Device";
		cout << endl << "5 - Return to Main Menu" << endl;
		
		do
		{
		cout << "Enter Menu Choice: ";
		cin >> response;
		cin.ignore(100, '\n');
		}while(response > 5 || response < 1);
		
		switch(response)
		{
			case 1:
				// change name of device
				ptr->change_name();
				break;
			
			case 2:
				// change description of device
				ptr->change_description();
				break;

			case 3:
				// pay bill of device
				ptr->pay_bill();
				break;

			case 4:
				//display device
				ptr->display();
				break;

			case 5:
				// end submenu
				break;
		}
	}while(response != 5);
}


/////* LIST FUNCTIONS *///////
// This class manages a linear linked list of devices
// it allows you to display, find an dadd devices

// constructor
list::list(): head(NULL)
{
}

// deconstructor
list::~list()
{
	if(head)
		delete_list(head);
}

// delete list
void list::delete_list(lnode *& head)
{
	if(!head)
		return;
		
	lnode * hold = head->get_next();
	delete head;
	head = hold;

	return delete_list(head);
}

// copy constructor
list::list(const list & copy): head(NULL)
{
	if(copy.head)
		copy_list(head, copy.head);
}

// remove devices of a contact
bool list::remove_devices()
{
	if(head)
	{
		delete_list(head);
		return true;
	}
	return false;
}

// copy list
void list::copy_list(lnode *& head, lnode * copy)
{
	if(!copy)
		return;
	
	lnode * temp = new lnode(copy);

	if(!head)
	{
		head = temp;
	}

	else
		head->set_next(temp);

	return copy_list(head->get_next(), copy->get_next());
}

// overload equal operator
list& list::operator = (const list& copy)
{
	if(this == &copy)
		return *this;
	// call copy function 
	copy_list(head, copy.head);

	return *this;
}

// display list
bool list::display()
{
	if(!head)
		return false;
	if(display(head))
		return true;
	return false;
}

// recursive function to display list
bool list::display(lnode * head)
{
	if(!head)
		return true;

	head->display();

	return display(head->get_next());
}

// add device to list
bool list::add_device(const device * toadd)
{
	if(!head)
	{
		head = new lnode(toadd);
		return true;
	}
	else
	{
		lnode * temp = new lnode(toadd);
		temp->set_next(head);
		head = temp;
		return true;
	}
	return false;
}

// find device in list
bool list::find_device(char * name)
{
	if(!head)
		return false;
	if(find_device(head, name))
		return true;
	return false;
}

// recursive function to find device in lll
bool list::find_device(lnode * head, char * name)
{
	if(!head)
		return false;

	// check if name passed matches 
	if(head->find_device(name))
		return true;

	return find_device(head->get_next(), name);
}

// return device ptr  wrapper function
device * list::return_device(char * name)
{
	if(!head)
		return NULL;
	else
		return return_device(head, name);
}

// return device ptr  recursively
device * list::return_device(lnode *& head, char * name)
{
	if(!head)
		return NULL;
	
	if(head->find_device(name))
		return head->return_device(name);
	
	return return_device(head->get_next(), name);
}


////* LNODE FUNCTIONS */////
// this class manages a node in a linear linked list
// the node points to a device object
// this class allows you to set the next node, find a device, display, etc

// constructor
lnode::lnode(): next(NULL)
{
	a_device = new device;
}

// deconstructor
lnode::~lnode()
{
	if(a_device)
		delete a_device;
}

// copy constructor
lnode::lnode(const lnode & copy): next(NULL)
{
	a_device = new device(*copy.a_device);
}

// copy constructor
lnode::lnode(const lnode * copy): next(NULL)
{
	// RTTI to great correct device for ocpy constructor
	const cell * ptr = dynamic_cast<const cell*>(copy->a_device);
	if(ptr)
	{
		a_device = new cell(*ptr);
	}

	const landline * ptr2 = dynamic_cast<const landline*>(copy->a_device);
	if(ptr2)
	{
		a_device = new landline(*ptr2);
	}

	const email * ptr3 = dynamic_cast<const email*>(copy->a_device);
	if(ptr3)
	{
		a_device = new email(*ptr3);
	}
}

// add constructor
lnode::lnode(const device *& copy): next(NULL)
{
	// RTTI to great correct device for ocpy constructor
	const cell * ptr = dynamic_cast<const cell*>(copy);
	if(ptr)
	{
		a_device = new cell(*ptr);
	}

	const landline * ptr2 = dynamic_cast<const landline*>(copy);
	if(ptr2)
	{
		a_device = new landline(*ptr2);
	}

	const email * ptr3 = dynamic_cast<const email*>(copy);
	if(ptr3)
	{
		a_device = new email(*ptr3);
	}
}

// assignment operator due to dynamic memory
lnode& lnode::operator = (const lnode& copy)
{
	if(this == &copy)
		return *this;

	if(a_device)
		delete a_device;
	
	a_device = new device(*copy.a_device);

	return *this;
}

// return the next node
lnode *& lnode::get_next()
{
	return next;
}

// set the next node to the argument
void lnode::set_next(lnode *& connection)
{
	next = connection;
}

// find device
bool lnode::find_device(char * name)
{
	if(a_device->find_device(name))
		return true;
	return false;
}

// display content of node
bool lnode::display()
{
	if(a_device)
	{
		if(a_device->display())
			return true;
	}
	return false;
}

// return device
device * lnode::return_device(char * name)
{
	return a_device;
}

//////*  TNODE FUNCTIONS */////////
// This class manages a node for a binary search tree

// constructor
tnode::tnode(): left(NULL), right(NULL), a_contact(NULL)
{
	a_contact = new contact;
}

// deconstructor
tnode::~tnode()
{
	if(a_contact)
		delete a_contact;
}

// copy constructor
tnode::tnode(const tnode & copy): left(NULL), right(NULL), a_contact(NULL)
{
	a_contact = new contact(*copy.a_contact);
}

// add constructor
tnode::tnode(const contact & copy): left(NULL), right(NULL), a_contact(NULL)
{
	a_contact = new contact(copy);
}

// set right node of BST
void tnode::set_right(tnode *& connection)
{
	right = connection;
}

// return the right node to the calling routine
tnode *& tnode::go_right()
{
	return right;
}

// return the left node to the calling routine
tnode *& tnode::go_left()
{
	return left;
}

// set left node of BST
void tnode::set_left(tnode *& connection)
{
	left = connection;
}

// display contact information
bool tnode::display_contact(char * name)
{
	if(a_contact->display())
		return true;
	return false;
}

// find contact in BST
bool tnode::find_contact(char * name)
{
	if(!a_contact)
		return false;
	if(a_contact->find_contact(name))
		return true;
	return false;
}

// add device to contact
bool tnode::add_device(device *& toadd)
{
	if(a_contact->add_device(toadd))
		return true;
	return false;
}

// display content of node
bool tnode::display()
{
	if(!(a_contact->display()))
		return false;
	else
	{
		if(a_contact->display_list())
			return true;
	return true;
	}


	return false;
}

// access submenu
void tnode::submenu(int & response)
{
	a_contact->submenu(response);
}

// remove devices from a contact
bool tnode::remove_devices()
{
	if(a_contact->remove_devices())
		return true;
	return false;
}

// compare name of contact with passed argument
bool tnode::compare_name(contact & cmp)
{
	if(a_contact->compare_name(cmp))
		return true;
	return false;
}

// compare name of contact with passed argument
bool tnode::compare_name(char * name)
{
	if(a_contact->compare_name(name))
		return true;
	return false;
}

// add contact of node
bool tnode::add(tnode *& copy)
{
	if(!copy->a_contact)
		return false;
	a_contact = copy->a_contact;
	return true;
}

// assignment operator due to dynamic memory
tnode& tnode::operator = (const tnode& copy)
{
	if(this == &copy)
		return *this;

	if(a_contact)
		delete a_contact;
	
	a_contact = new contact(*copy.a_contact);

	return *this;
}

//////* TABLE FUNCTIONS *///////
// This class manages a binary search tree of contacts
// It allows you to display contacts, find contacts, and remove contacts
// contains a root 

// constructor
table::table(): root(NULL)
{
}

// deconstructor
table::~table()
{
	if(root)
		delete_table(root);
}

// remove all wrapper function
bool table::delete_table()
{
	if(root)
	{
		delete_table(root);
		root = NULL;
		return true;
	}
	else
		return false;
}

// delete table 
void table::delete_table(tnode *& root)
{
	if(!root)
		return;

	delete_table(root->go_left());

	delete root;

	delete_table(root->go_right());
}

// copy constructor
table::table(const table & copy)
{
	// check if item to copy is empty
	if(copy.root)
		copy_table(root, copy.root);
}

// copy roots data to table
void table::copy_table(tnode * root, tnode * copy)
{
	if(!copy)
		return;
	
	root = new tnode(*copy);

	copy_table(root->go_left(), copy->go_left());
	copy_table(root->go_right(), copy->go_right());
}

// remove devices from a contact
bool table::remove_devices(char * contact_name)
{
	if(find_contact(this->root, contact_name))
	{
		tnode * temp = return_contact(root, contact_name);
		if(temp)
			if(temp->remove_devices())
				return true;
	}
	return false;
}

// display all contacts in BST
bool table::display_all_contacts()
{
	if(root)
	{
		display_all_contacts(root);
		return true;
	}
	return false;
}

// display all contacts in BST recursively
void table::display_all_contacts(tnode *& root)
{
	if(!root)
		return;

	display_all_contacts(root->go_left());
	root->display();
	display_all_contacts(root->go_right());
}

// add contact to table
bool table::add_contact(contact & copy)
{
	if(!root)
	{
		root = new tnode(copy);
		return true;
	}
	else
	{
		add_contact(copy, root);
	}
	return false;
}

// recursively to add contact to table
bool table::add_contact(contact & copy, tnode *& root)
{
	if(!root)
	{
		root = new tnode(copy);
		return true;
	}
	
	// if current root name is greater than or equal to comparision name, go left
	if(root->compare_name(copy))
	{
		add_contact(copy, root->go_left());
	}
	// otherwise, the root is smaller than the comparison, go right 
	else
	{
		add_contact(copy, root->go_right());
	}
}

// display a specific contacts LLL
bool table::display_contact(char * name)
{
	if(find_contact(this->root, name))
	{
		tnode * temp = return_contact(root, name);
		if(temp)
			if(temp->display())
				return true;
	}
	return false;
}

// find contact in table
bool table::find_contact(tnode *& root, char * name)
{
	if(!root)
	{	
		return false;
	}
	
	// if name match, return true;
	if(root->find_contact(name))
		return true;
	
	// if name argument is less then or equal to root
	if(root->compare_name(name))
		find_contact(root->go_left(), name);
	// otherwise go right
	else
		find_contact(root->go_right(), name);
}

// find contact in table and return to calling routine
tnode * table::return_contact(tnode *& root, char * name)
{
	if(!root)
	{	
		return NULL;
	}

	if(root->find_contact(name))
	{
		return root;
	}
		
	// if root is greater or equal to name, go left
	if(root->compare_name(name))
		return_contact(root->go_left(), name);
	else
		return_contact(root->go_right(), name);
}

// add device to contact to BST
bool table::add_device(device *& toadd, char * name)
{
	tnode * temp = return_contact(root, name);
	if(temp)
	{
		if(temp->add_device(toadd))
			return true;
		return false;
	}

	return false;
}

// remove contact from BST
bool table::remove_contact(char * name)
{
	if(!root)
		return false;
	else
	{
		if(remove_contact(root, name))
			return true;
	}

}

// access submenu of contact
bool table::submenu(char * name, int & response)
{
	if(find_contact(root, name))
	{
		tnode * temp = return_contact(root, name);
		temp->submenu(response);
		return true;
	}

}

//remove contact from BST recursively
bool table::remove_contact(tnode *& root, char * name)
{
	if(!root)
	{	
		return false;
	}

	if(root->find_contact(name))
	{
		remove_node(root);
		return true;
	}
		
	// if root is greater or equal to name, go left
	if(root->compare_name(name))
		remove_contact(root->go_left(), name);
	else
		remove_contact(root->go_right(), name);
	return false;
}

// remove node from BST
bool table::remove_node(tnode *& root)
{
	tnode * hold = NULL;

	// empty truee
	if(!root)
		return false;
	
	// no children
	if(!root->go_right() && !root->go_left())
	{
		delete root;
		root = NULL;
		return true;
	}

	// only left child - left child becomes root
	if(!root->go_right() && root->go_left())
	{
		hold = root->go_left();
		delete root;
		root = hold;
		return true;
	}

	// only right child, right becomes root
	if(root->go_right() && !root->go_left())
	{
		hold = root->go_right();
		delete root;
		root = hold;
		return true;
	}

	// two children
	if(root->go_right() && root->go_left())
	{
		hold = root->go_right();
		tnode * child = NULL;

		if(!hold->go_left())
		{
			hold = root->go_right();
			child = hold->go_right();

			// add right child to root
			if(!(root->add(hold)))
				return false;

			root->go_right() = child;
			delete hold;
			return true;
		}
		else
		{
			tnode * parent = NULL;

			while(hold->go_right())
			{
				hold->go_right();
			}
			child = hold->go_right();

			// add smallest value to object to the root
			if(!(root->add(hold)))
				return false;

			delete hold;
			hold = NULL;

			parent->set_left(child);
			return true;
		}
	}
	return false;
}

// table assignment operator due to dynamic memory
table& table::operator = (const table& copy)
{
	if(this == &copy)
		return *this;
	// call copy function 
	copy_table(root, copy.root);

	return *this;
}
