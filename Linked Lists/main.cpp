#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>

#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"
#include "NodeList.h"


using namespace std;


int main(int argc, char** argv) {
    
    string line, command;
    NodeList circuit;// = new circuit;
    
    cout << "> ";
    
    getline (cin, line); //retrieve stream from input and place it in line
    
    /*
     //allow input to be read from a file for ease of testing
     //must be commented for submission
     ifstream inFile;
     inFile.open("test.txt");
     
     if (!inFile) {
     cout << "Unable to open file test.txt";
     }
     else {
     
     }
     */
    
    
    while ( !cin.eof() ) {
        
        
        //cout << line << endl;
        
        stringstream lineStream (line); // create stringstream with line as contents
        lineStream >> command;          // read the first item in the stream
        
        if(checkStreamErrors(lineStream))
            cout << "Error: invalid command" << endl;      //will execute if there is a flag raised by command
        else{                                                //parse individual commands if there is no error
            if(command == "insertR"){
                cout << insertR(lineStream, circuit) << endl;
            }
            else if (command == "modifyR"){
                cout << modifyR(lineStream, circuit) << endl;
            }
            else if (command == "printR"){
                cout << printR(lineStream, circuit) << endl;
            }
            else if (command == "printNode"){
                cout << printNode(lineStream, circuit);
            }
            else if (command == "deleteR"){
                cout << deleteR(lineStream, circuit) << endl;
            }
            else if (command == "setV"){
                cout << setV(lineStream, circuit) << endl;
            }
            else if (command == "unsetV"){
                cout << unsetV(lineStream, circuit) << endl;
            }
            else if (command == "solve"){
                cout << solve(circuit) << endl;
            }
            else{   //if command doesn't raise flags but doesn't match a command
                cout << "Error: invalid command" << endl;
            }
        }
        
        //reset flags and clear stream
        lineStream.clear();
        lineStream.ignore(1000, '\n');
        
        cout << "> ";
        getline(cin, line);
        //ask for next input
        
    } //repeat until EOF is entered
    
     //inFile.close(); //closes file once everything has been parsed
    
    //clean up circuit before exiting to prevent memory leaks
    circuit.deleteAll();
    
    return 0;
}

