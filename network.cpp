
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <dirent.h> // directory+entry

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    loadDB(fileName);

}

Network::~Network(){
    // Copy from lab5 
    Connection* ptr = head;
    while(head != NULL){
        ptr = head->next;
        delete head;
        head = ptr;
        count--;
    }
}


void Network::push_front(Connection* newEntry){
    // Adds a new Connection (newEntry) to the front of LL
    // TA completed me in lab5 and since then I've not been changed! 
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Connection* newEntry){
    // Adds a new Connection (newEntry) to the back of LL
    // Copy from your lab5
    newEntry->prev = tail;
    newEntry->next = NULL;

    if(tail != NULL)
        tail->next = newEntry;
    else
        head = newEntry;

    tail = newEntry;
    count++;
}


Connection* Network::search(Connection* searchEntry){
    // Searches the Network for searchEntry
    // if found, returns a pointer to it, else returns NULL
    // Copy from lab5 
    Connection* ptr = head;
    while(ptr != NULL)
    {

        if(*ptr==*searchEntry)
        {
            return ptr;

        }else{


            ptr = ptr->next;
 
        }

    }
    return ptr;
}


Connection* Network::search(string fname, string lname){
    // New == for Connection, only based on fname and lname
    // if found, returns a pointer to it, else returns NULL
    // TODO: Complete this method
    // Note: two ways to implement this, 1st making a new Connection with fname and lname and and using search(Connection*), 2nd using fname and lname directly. 

    Connection* ptr = head;
    while(ptr != NULL)
    {
        
        if((ptr->f_name == fname) && (ptr->l_name == lname))
        {
            return ptr;
        }else{
            ptr = ptr->next;
        }
    }

    return NULL;

}


void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Connection attributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of connections: " << count << endl;
    cout << "------------------------------" << endl;
    Connection* ptr = head;
    while(ptr != NULL){
        ptr->print_connection();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::saveDB(string filename){
    // Saves the netwrok in file <filename>
    // Note: The format of the output file is very abstract, just raw data
    // Look at studentDB.txt as a template
    // TODO: Update this method with new requirements
    // Note: notice the intentional flaw in this code, as compared to the note mentioned in printDB, 
    //now the one who is responsible for implementing Network should be aware of implementation of Connection, not good! You will fix this in PA2. 

    ofstream o;
    o.open(filename.c_str());
    Connection* ptr = head;
 
    while(ptr != NULL)
    {
        o << ptr->l_name << ", ";
        o << ptr->f_name << endl;
        o << ptr->birthdate->get_date() << endl;
        o << ptr->email->get_contact()<< endl;
        o << ptr->phone->get_contact()<< endl;
        o << "------------------------" << endl;
        ptr = ptr->next;
    }
    o.close();
}


void Network::loadDB(string filename){
    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them
    // TODO: Now you will notice you need to go back and make a new constructor to the Connection class,  
    // Connection::Connection(fname, lname, bdate, email, phone)
    // TODO: Update this method with new requirements 

    Connection* ptr = head;
    while(head != NULL){
        ptr = head->next;
        delete head;
        head = ptr;
        count--;
    }
    head = NULL;
    tail = NULL;
    ifstream infile;
    infile.open(filename.c_str());
    string buff, fname, lname, bdate, phone, email;
    while(getline(infile, buff)){
        lname = buff.substr(0, buff.find(','));
        fname = buff.substr(buff.find(',')+2);
        getline(infile, bdate);
        getline(infile, email);
        getline(infile, phone);
        getline(infile, buff);
        Connection* newEntry = new Connection(fname, lname, bdate, email, phone);
        this->push_back(newEntry);
    }


}


bool Network::remove(string fname, string lname){
    // We modified the definition of == for Connection in Connection definition itself, 
    // So we should not be worried about changes we made in Connection to modify this method!
    // Copy from lab5
    //Connection* remover = search(fname,lname);
    Connection* temp = search(fname,lname);

    if(temp != NULL)
    {
        if(temp->prev == NULL)
        {
            head = head->next;
            //delete remover;
            delete temp;
            head->prev = NULL;
            count--;
        }else if(temp->next == NULL)
        {
            tail = tail->prev;
            //delete remover;
            delete temp;
            tail->next = NULL;
            count--;
        }else if(temp->prev == NULL && temp->next == NULL)
        {
            //delete remover;
            delete temp;
            count--;

        }else{

            Connection* temp_next = temp->next;
            Connection* temp_prev = temp->prev;

            temp_next->prev = temp_prev;
            temp_prev->next = temp_next;   
            count--; 
            delete temp;
            //delete remover;

        }

        return true;

    }else{
       // delete remover;
        delete temp;
        return false;

    }
}


void Network::sendEmail(string addr, string subject, string content, string attachment=""){
    // Sending a command looks like:
    // echo "content" | mailx -s "subject" -a "attachment" addr;
    // TODO: Search how you can run a unix command in C++
    // TODO: You need to add double quotation character (") to both sides of strings for this command. Adding other characters (like ? in code below) should be easy, but double quotation says: I'm a character but not a typical character! 
    // string new_str = '?' + old_str + '?'
    // TODO: Complete this method

    content = "\"" + content + "\"";
    subject = "\"" + subject + "\"";
    attachment = "\"" + attachment + "";
    string cmd;
    cmd = "echo " + content + " | mailx -s " + subject + " -a " + attachment + addr;
    cout << cmd << endl;
    system(cmd.c_str());



}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new connection \n";
        cout << "4. Remove a connection \n";
        cout << "5. Search \n";
        cout << "6. Send an email \n";
        cout << "7. Send an iMessage \n";
        cout << "8. Print database \n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            cin >> fileName;
            saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){
            // TODO: Complete me!
            cout << "Loading network database \n";
            // TODO: print all the files in this same directory that have ".db" format

            int flag = 0;
            DIR *dir;
            struct dirent *ent;
            char targetFolderAddr[] = "./";
            if ((dir = opendir ("./")) != NULL)
            {

                  while (((ent = readdir (dir)) != NULL ) || flag == 0 || flag == 1) {

                    if(flag == 0)
                    {
                        if (ent == NULL)
                        {   
                            flag = 1;
                            rewinddir(dir);
                            ent = readdir(dir);
                            
                        }
                   
                        
                        int length = strlen(ent->d_name);

                        if (strncmp(ent->d_name + length - 3, ".db", 3) == 0) 
                        {
                            cout << ent->d_name << endl;

                        }
 
                    }
                    if(flag == 1)
                    {
                        cout << "Enter the name of the load file: ";
                        cin >> fileName;
                        flag =2;
                        
                    }

                    if(ent->d_name == fileName && flag == 2)
                    {
                        loadDB(fileName);
                        cout << "Network loaded from " << fileName << " with " << count << " connections \n";
                        flag =3;
                        break;
                    }
                      
                  }
                  if(flag!=3)
                  {
                    cout << "FILENAME does not exist!" << endl;
                  }
                  
                  closedir (dir);

            } else {
                  /* could not open directory */
                  perror ("No directory!");

            }





 
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new Connection ONLY if it does not exists!
            Connection* newEntry = new Connection();
            Connection* ptr = search(newEntry);
            if(ptr == NULL)
            {
                cout << "Adding a new connection \n";
                push_front(newEntry);
            }
            
        }
        else if (opt == 4){
            // TODO: Complete me!
            cout << "Removing a connection \n";
            cout << "First name: ";
            std::getline(std::cin,fname);
            cout << "Last name: ";
            std::getline(std::cin,lname);
            bool rmv = remove(fname,lname);
            if(rmv)
            {
                cout << "Remove Successful! \n";
            }else{
                cout << "Connection not found! \n";
            }

        }
        else if (opt==5){
            // TODO: Complete me!
            cout << "Searching: \n";
            cout << "First Name: ";
            std::getline(std::cin, fname);
            cout << "Last Name: ";
            std::getline(std::cin, lname);
            Connection* ptr = search(fname,lname);
            if(ptr!=NULL)
            {
                ptr->print_connection();
            }else{
                cout << "Not found! \n";
            }
            // if found: print connection
            // if not, cout << "Not found! \n";
        }
        else if (opt==6){
            // Note: Completed!
            cout << "Sending email to: \n";
            cout << "First Name: ";
            std::getline (std::cin, fname);
            cout << "Last Name: ";
            std::getline (std::cin, lname);
            Connection* ptr = search(fname, lname);
            if (ptr){
                string subject, content, attachment;
                cout << "Sending email to: \n";
                ptr->print_connection();
                cout << "Subject: ";
                std::getline (std::cin, subject);
                cout << "Content: ";
                std::getline (std::cin, content);
                cout << "Attachment: ";
                std::getline (std::cin, attachment);
                string addr = ptr->email->get_contact("1");
                sendEmail(addr, subject, content, attachment);
            }
            else 
                cout << "Contact not found! \n";
        }
        else if (opt==7){
            cout << "Option currently not available\n";
        }
        else if (opt==8){
            // TODO: Complete me!
            cout << "Network Database: \n";
            printDB();
        }
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}


