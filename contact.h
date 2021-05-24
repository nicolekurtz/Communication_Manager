//Nicole Kurtz
#include "device.h"


// this class manages a node in a linear linked list
// the node points to a device object
// this class allows you to set the next node, find a device, display, etc
class lnode
{
	public:
		lnode(); // constructor
		~lnode(); // deconstructor
		lnode(const lnode & copy); // copy constructor
		lnode(const lnode * copy); // copy constructor
		lnode(const device *& copy); // add constructor
		lnode *& get_next(); // return the next node
		void set_next(lnode *& connection); // set next node in LLL
		bool find_device(char * name); // check if name matches contact device name
		bool display(); // display content of node
		device * return_device(char * name); // return device ptr

		lnode& operator = (const lnode& copy); // asignment operator due to dynamic memory
	private:
		lnode * next; // next pointer
		device * a_device; // a pointer to a device
};

// This class manages a linear linked list of devices
// it allows you to display, find an dadd devices
class list
{
	public:
		list(); // constructor
		~list(); // deconstructor
		list(const list & copy); // copy constructor
		bool display(); // display list of devices
		bool add_device(const device * toadd); // add device to lll
		bool find_device(char * name); // find device in LLL
		bool remove_devices(); // remove a contacts devices
		device * return_device(char * name); // return pointer to device

		list& operator = (const list&); // set list to argument list info
	private:
		bool find_device(lnode * head, char * name); // recursive fnction to find device
		device * return_device(lnode *& head, char * name); // return pointer to device
		void copy_list(lnode *& head, lnode * copy); // copy list to head
		void delete_list(lnode *& head); // delete list 
		bool display(lnode * head); // recursive function to display list
		lnode * head; // head of LLL
};

// this class manages a class object that contains a dynamic character name.
// It has a linear linked list of device
class contact
{
	public:
		contact(); // constructor
		~contact(); // deconstructor
		contact(const contact & copy); // copy constructor
		bool add_contact(char * name); // create contact
		bool display(); // display contact information
		bool display_list(); // display the contents of the device list
		bool find_contact(char * name); // compare contact name to argument name
		bool add_device(device *& copy); // add device to contact
		bool compare_name(contact & cmp); // compare name to argment
		bool compare_name(char * name); // compare name to argment
		bool add_cellphone(); // create cellphone object
		void submenu(int & response); // access device submenu
		bool remove_devices(); // remove devices from a contact
	
		contact& operator = (const contact& copy); // asignment operator due to dynamic memory

	private:	
		String * name; // name of contact
		list * device_list; // list of devices
};

// This class manages a node for a binary search tree
class tnode
{
	public:
		tnode(); // constructor
		~tnode(); // deconstructor
		tnode(const tnode & copy); // copy constructor
		tnode(const contact & copy); // add constructor
		void set_right(tnode *& connection); // set right ptr of node to argument
		void set_left(tnode *& connection); // set left ptr of node to argument
		tnode *& go_right(); // return right node
		tnode *& go_left(); // return left node
		bool display(); // display contact and LLL
		bool display_contact(char * name); // display contact information
		bool compare_name(contact & cmp); // compare name of contact argument and current node contact
		bool remove_devices(); // remove devices from a contact
		bool compare_name(char * name); // compare name of contact argument and current node contact
		bool find_contact(char * name); // find contact in BST
		bool add_device(device *& toadd); // add device to node
		bool add(tnode *& add); // add node
		void submenu(int & response); // access submenu of contact
		
		tnode& operator = (const tnode& copy); // assignment operator due to dynamic memory

	private:
		contact * a_contact;
		tnode * left; // left ptr
		tnode * right; // right ptr
};


// This class manages a binary search tree of contacts
// It allows you to display contacts, find contacts, and remove contacts
class table
{
	public:
		table(); // constructor
		~table(); // deconstructor
		table(const table & copy); // copy constructor
		bool display_all_contacts(); // display all contacts in BST
		bool display_contact(char * name); // display a specific contact
		bool add_device(device *& toadd, char * name); // add device to contact to BST
		bool remove_contact(char * name); // remove contact from BST
		bool add_contact(contact &); // add contact to table
		bool submenu(char * name, int & response); // submenu access of contact list
		bool delete_table(); // delete table wrapper function
		bool remove_devices(char * contact_name); // remove devices from a contact

		table& operator = (const table& copy); // assignment operator due to dynamic memory

	private:
		tnode * root; // root of BST
		tnode * return_contact(tnode *& root, char * name); // find contact and return node to calling routine
		bool find_contact(tnode *& root, char * name); // find contact in BST
		bool remove_node(tnode *& root); // remove node from BST
		void display_all_contacts(tnode *& root); // display all contacts recursively
		bool remove_contact(tnode *& root, char * name); //re move contact from BST
		void copy_table(tnode * root, tnode * copy); // copy table contents
		void delete_table(tnode *& root); // delete table 
		bool add_contact(contact & copy, tnode *& root); // recursively add contact to BST
};
