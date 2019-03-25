
#include "contact.h"
// TODO: Add needed libraries! 


//concerns: not sure i can do this->type = type and this->email = email in the Email:: set_contact() method but WHO KNOWS

Email::Email(string type, string email_addr){
    // TODO: Complete me!
    this->type = type;
    this-> email_addr = email_addr;
}


void Email::set_contact(){
    // TODO: Do not change the prompts!
	
    cout << "Enter the type of email address: ";
    // some code here
    std::getline (std::cin,type);
    this->type = type;
    cout << "Enter email address: ";
    // some code here
    std::getline (std::cin,email_addr);
    this->email_addr = email_addr;
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    if (style=="full")
    {
        return "Email (" + type + ") " + email_addr;
    }
        

    else
    {
        return email_addr;
    }
        
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


Phone::Phone(string type, string num){
    // TODO: It is possible that num includes "-" or not, manage it!
    // TODO: Complete this method!
    // Note: We don't want to use C++11! stol is not valid!
    // The code has been covered in the discussion session

    // Note: Understand your own TA's bug!
    //* This code has a bug, can you understand why?
    string a_code, mid, end;
    if(num.find("-") == 3)
    {
        a_code = num.substr(0,3).c_str();

        if(num.find("-", 4) == 7)
        {
            mid = num.substr(4,3).c_str();
            end = num.substr(8).c_str();
        }else{
            mid = num.substr(4).c_str();
        }

    }else if(num.find("-") == 6){

        a_code = num.substr(0,6).substr();
        mid = num.substr(7).c_str();

    }else{
        a_code = num;
    }

    num = a_code + mid + end;


    long int area_code = atoi(num.substr(0, 3).c_str());
    long int  number = atoi(num.substr(3).c_str()); 
    this->phone_num = area_code*10000000 + number; 
    this->type = type;
    
}


void Phone::set_contact(){
    // TODO: Complete this method
    // Use the same prompts as given!
    string a_code, mid, end;
	cout <<"Enter the type of phone number: ";
    std::getline (std::cin,type);
	cout << "Enter the phone number: ";
    std::getline (std::cin,numby);
    //filters out all possible "-"
    if(numby.find("-") == 3)
    {
        a_code = numby.substr(0,3).c_str();

        if(numby.find("-", 4) == 7)
        {
            mid = numby.substr(4,3).c_str();
            end = numby.substr(8).c_str();
        }else{
            mid = numby.substr(4).c_str();
        }

    }else if(numby.find("-") == 6){

        a_code = numby.substr(0,6).substr();
        mid = numby.substr(7).c_str();

    }else{
        a_code = numby;
    }

    numby = a_code + mid + end;
    this->phone_num = atol(numby.c_str());

}


string Phone::get_contact(string style){
    // TODO: Complete this method, get hint from Email 
    // The code has been covered in discussion session 

    // Note: Understand your own TA's bug!
    // This code has a bug, can you understand it!
    long int x1 = (this->phone_num/10000000); //gets rid of back 7 digits 
    long int x2 = ((this->phone_num)/10000)%10000; //removes front 3 digits then removes back 4 digits
    long int x3 = (this->phone_num)%10000; //removes front 6 digits
    string s1 = std::to_string(x1);
    string s2 = std::to_string(x2);
    string s3 = std::to_string(x3);
    string l = s1 + s2 + s3;
    if(style == "full")
    {

        return "Phone (" + type + ") " + l;
    }else{
        return l;
    }

  
    
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


