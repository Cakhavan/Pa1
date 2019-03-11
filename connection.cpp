
#include "connection.h"

Connection::Connection(){
    // I'm already done! 
    set_connection();
}


Connection::~Connection(){
    // TODO: Complete me!
    delete birthdate;
}


Connection::Connection(string f_name, string l_name, string bdate, string email, string phone){
    // TODO: Complete this method!
    // phone and email strings are in full version
    this->f_name = f_name;
    this->l_name = l_name;
    this->birthdate = new Date(bdate);
    this->email = new Contact("email", email);
    this->phone = new Contact("phone", phone);
}


Connection::Connection(string filename){
    // TODO: Complete this method!
    set_connection(filename);

}


void Connection::set_connection(){
    // prompts for the information of the user
    // first/last name can have spaces! (can't use cin)
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    string temp;
    string type;

    cout << "First Name: ";
    std::getline (std::cin,f_name);
	cout << "Last Name: ";
    // code here
    std::getline (std::cin,l_name);
    cout << "Birthdate (M/D/YYYY): ";
    std::getline (std::cin,temp);
    birthdate = new Date(temp);
    
    cout << "Type of email address: ";
    std::getline(std::cin,type);
    cout << "Email address: ";
    std::getline(std::cin,temp);

    email = new Contact(type,temp);


    cout << "Type of phone number: ";
    std::getline(std::cin,type);
    cout << "Phone number: ";
    std::getline(std::cin,temp);
    phone = new Contact(type,temp);
}


void Connection::set_connection(string filename){
    // TODO: Complete this method!
    // Look at connection_template files as examples.     
    // Phone number in files can have '-' or not.

    // Open the file <filename>
    ifstream file;
    file.open(filename.c_str());
    // Look at connection_template.txt 
    // Line #1: "first name, lastname"
    string line;
    getline(file, line);
    cout << "First Name: " << f_name << endl;
    this->f_name =  line.substring(0,line.indexOf(','));
    cout << "Last Name: " << this->l_name << endl;
    this->l_name = line.substring(line.indexOf(',')+1,line.length()-line.indexOf(','));
    // Line #2: date of birth in string format 
    getline(file, line);
    this-> birthdate = new Date(line);

    //line #3
    getline(file, line);
    string type = line.substring(0,line.indexOf(')'));
    string email = line.substring(line.indexOf(')')+1, line.length()-1);
    this->email = new Contact(type, email);
    cout << "type: " << type << endl;
    cout << "email: " << email << endl;

}


bool Connection::operator==(const Connection& rhs){
    // TODO: Complete this method!
    // Note: Difference to Lab is that from now on the combination of fname-lname is unique for any connection
    if ( (this->f_name == rhs.f_name) && (this->l_name == rhs.l_name) 
        && (this->birthdate->operator==(*rhs.birthdate)) && (this->email == rhs.email) && (this->phone == rhs.phone))
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool Connection::operator!=(const Connection& rhs){ 
    // TODO: Complete this method!
    return !(*this == rhs);
}


void Connection::print_connection(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    email->print();
    phone->print();
}

