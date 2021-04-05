#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

#include "TreeDB.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    string line, command;
    TreeDB server;
    
    cout << "> ";
    
    /*//used for testing from a file
    ifstream inFile;
    inFile.open("test.txt");

    getline(inFile, line);
    cout << line << endl;
    */
    getline(cin, line);
    
    
    while (!cin.eof()) {
        //read command from input
        stringstream lineStream (line);
        lineStream >> command;
        
        //parse command and execute relevant function
        if (command == "insert") {
            //parse input
            string name, readActive;
            unsigned int IPaddress;
            bool active = false;
            
            lineStream >> name >> IPaddress >> readActive;
            if (readActive == "active")
                active = true;
            DBentry* input = new DBentry(name, IPaddress, active);
            
            //insert node and print outcome
            if(server.insert(input))
                cout << "Success" << endl;
            else{
                cout << "Error: entry already exists" << endl;
                delete input;
            }
        }
        else if (command == "find"){
            //parse input
            string name;
            lineStream >> name;
            DBentry* result = server.find(name);
            
            //find node and print outcome
            if(result == NULL){
                cout << "Error: entry does not exist" << endl;
            }
            else
                cout << *result << endl;
        }
        else if (command == "remove"){
            //parse input
            string name;
            lineStream >> name;
            
            //remove node and print outcome
            if(server.remove(name)){
                cout << "Success" << endl;
            }
            else
                cout << "Error: entry does not exist" << endl;
        }
        else if (command == "printall"){
            //print all nodes in database
            cout << server;
        }
        else if (command == "printprobes"){
            //parse input
            string name;
            lineStream >> name;
            
            //print number of steps to get to a node or print error
            if(server.find(name) == NULL)
                cout << "Error: entry does not exist" << endl;
            else
                server.printProbes();
        }
        else if (command == "removeall"){
            //empty the database
            server.clear();
            cout << "Success" << endl;
        }
        else if (command == "countactive"){
            //count the nodes that are active and print that number
            server.countActive();
        }
        else if (command == "updatestatus"){
            //parse input
            string name, readActive;
            bool active = false;
            lineStream >> name >> readActive;
            if (readActive == "active")
                active = true;
            
            //update the active status of selected node and print outcome
            if(server.find(name) == NULL)
                cout << "Error: entry does not exist" << endl;
            else{
                server.find(name)->setActive(active);
                cout << "Success" << endl;
            }
        }
        else    //if command doesn't match a predefined operation
            cout << "Error: Invalid command" << endl;
        
        //prepare stream for next input
        lineStream.clear();
        lineStream.ignore(1000, '\n');
        
        cout << "> ";
        
        getline(cin, line);
        //cout << line << endl;
    }
    
    //inFile.close();
    return 0;
}
