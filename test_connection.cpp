
#include <iostream>
#include "connection.h"

int main(){

    Connection c1;
    c1.print_connection();
    cout << "----------------\n";

    Connection c2("studentDB.db");
    cout << "----------------\n";



    return 0;
}
