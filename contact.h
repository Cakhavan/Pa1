
#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>

// TODO: You may need to add other libraries here!
using namespace std;


class Contact {
    // TODO: private or protected? Look at your children!
protected:	
	string type;
public:
	virtual void print() = 0;
    virtual string get_contact(string style="full") = 0;
	virtual void set_contact() = 0;

};


class Email: public Contact{
private:
    string email_addr;
public:
    void print();
    string get_contact(string style="full");
    void set_contact();
    Email(string type, string email_addr);
 
    // TODO: Complete me!
};


class Phone: public Contact{
private:
    // TODO: modify dataType! Can int store 10 digit phone-number? 
	long int phone_num; 
public:
    void print();
    string get_contact(string style ="full");
    Phone(string type, string phone_number);
    void set_contact();
 
    
    string numby;
    // TODO: Complete me!
};

#endif
