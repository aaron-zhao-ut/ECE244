#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "Rparser.h" //function declarations used in this file

using namespace std;

string insertR(stringstream & stream, NodeList & circuit){
    //initialize required insertR variables
    string name;
    double resistance;
    int nodeId[2];
    
    stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    
    //parse name
    stream >> name;
    if(checkStreamErrors(stream)){
        return("Error: invalid argument");
    }
    else if (checkNameAll(name)){
        return("Error: resistor name cannot be the keyword \"all\"");
    }
    else if (circuit.resExists(name))
        return(string("Error: resistor ") + name + string(" already exists"));
    stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    
    //parse resistance
    stream >> resistance;
    if (checkStreamErrors(stream)){
        return("Error: invalid argument");   
    }
    else if (checkResistance(resistance)){
        return("Error: negative resistance");
    }
    stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    
    //parse first nodeID
    stream >> nodeId[0];
    if (checkStreamErrors(stream) || (stream.peek()=='.')){
        return("Error: invalid argument");
    }
    else if (validInt(stream)){
        return("Error: invalid argument");
    }
    stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    
    //parse second nodeID
    stream >> nodeId[1];
    if (checkStreamErrors(stream) || (stream.peek()=='.')){
        return("Error: invalid argument");
    }
    else if (validInt(stream)){
        return("Error: invalid argument");
    }
    else if(nodeId[0] == nodeId[1]){
        string sameNodeError;
        stringstream ss;
        ss << "Error: both terminals of resistor connect to node " << nodeId[0];
        getline(ss, sameNodeError);
        return(sameNodeError);
    }
    stream >> ws;
    if (!stream.eof())
        return("Error: too many arguments");

    //if no initial parsing errors: proceed with backend update and return success message
    return(insertRSuccess(name, resistance, nodeId, circuit));
}

string modifyR(stringstream & stream, NodeList & circuit){
    
    //initialize required modifyR variables
    string name;
    double resistance;
    
    stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    
    //parse name
    stream >> name;
    if(checkStreamErrors(stream))       
        return("Error: invalid argument");
    else if (checkNameAll(name))
        return("Error: resistor name cannot be the keyword \"all\"");
    else if (!circuit.resExists(name))
        return(string("Error: resistor ") + name + string(" not found"));
    stream >> ws;
    if (stream.eof())
        return("Error: too few arguments");
    
    //parse resistance
    stream >> resistance;
    if (checkStreamErrors(stream))
        return("Error: invalid argument");
    else if (checkResistance(resistance))
        return("Error: negative resistance");
    stream >> ws;
    if (!stream.eof())
        return("Error: too many arguments");
    
    //if no initial parsing errors: proceed with backend update and return success message
    return(modifyRSuccess(name, resistance, circuit));
}

string printR(stringstream & stream, NodeList & circuit){
    
    //initialize required printR variables
    string name;

    stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    
    //parse name
    stream >> name;
    if(checkStreamErrors(stream))
        return("Error: invalid argument");
    else if (checkNameAll(name))
        //if no initial parsing errors: proceed with printAll and return success message
        return(printRSuccessAll(circuit));
    
    stream >> ws;
    if (!stream.eof())
        return("Error: too many arguments");
    
    if(!circuit.resExists(name))
        return(string("Error: resistor ") + name + string(" not found"));
    
    //if no initial parsing errors: proceed with print and return success message
    return(printRSuccess(name, circuit));
}

string printNode(stringstream & stream, NodeList & circuit){
    
    //initialize required printNode variables
    int nodeId;
    string all;
    stringstream ss;

    stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    
    //parse nodeID. PrintAll if key word all is detected
    stream >> nodeId;
    if(stream.fail() || ((stream.peek() != ' ') && !stream.eof())){
        stream.clear(); //lower flags
        stream >> all;        
        if(all == "all"){
            stream >> ws;
            if (!stream.eof())
                return("Error: too many arguments");
            
            //if no initial parsing errors: proceed with print and return success message
            else return(printNodeSuccessAll(circuit));
        }
        else return("Error: invalid argument");
    }
    if (validInt(stream))
        return("Error: invalid argument");
    stream >> ws;
    if (!stream.eof())
        return("Error: too many arguments");
    if(circuit.findNode(nodeId) == NULL)
       return(string("Error: node ") + to_string(nodeId) + string(" not found"));
    
    //if no initial parsing errors: proceed with print and return success message
    return(printNodeSuccess(nodeId, circuit));
}

string deleteR(stringstream & stream, NodeList & circuit){
    
    //initialize required deleteR variables
    string name;

    stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    
    stream >> name;
    
    if(checkStreamErrors(stream))
        return("Error: invalid argument");   

    else if (checkNameAll(name)){
        stream >> ws;
        if (!stream.eof())
            return("Error: too many arguments");
        
        //if no initial parsing errors: proceed with backend update and return success message
        return(deleteRSuccessAll(circuit));
    }
    stream >> ws;
    if (!stream.eof())
        return("Error: too many arguments");
    
    //if no initial parsing errors: proceed with backend update and return success message
    return(deleteRSuccess(circuit, name));
}

string setV(stringstream & stream, NodeList & circuit){
    int nodeId;
    double voltage;
    stringstream ss;
    
    stream >> ws;
    if (stream.eof())
        return("Error: too few arguments");
    
    stream >> nodeId;
    if (checkStreamErrors(stream) || (stream.peek()=='.')){
        return("Error: invalid argument");
    }
    else if (validInt(stream)){
        return("Error: invalid argument");
    }
    stream >> ws;
    if (stream.eof())
        return("Error: too few arguments");
    
    if(circuit.findNode(nodeId) == NULL)
        return(string("Error: node ") + to_string(nodeId) + string(" not found"));
    
    stream >> voltage;
    if(checkStreamErrors(stream))
        return("Error: invalid argument");
    
    circuit.findNode(nodeId)->setV(voltage);
    
    string success;
    ss << "Set: node " << nodeId << " to " << fixed << setprecision(2) << voltage
    << " Volts";
    getline (ss, success);
    return(success);
    
}
string unsetV(stringstream & stream, NodeList & circuit){
    int nodeId;
    stringstream ss;
    
    stream >> ws;
    if (stream.eof())
        return("Error: too few arguments");
    
    stream >> nodeId;
    if (checkStreamErrors(stream) || (stream.peek()=='.')){
        return("Error: invalid argument");
    }
    else if (validInt(stream)){
        return("Error: invalid argument");
    }
    
    if(circuit.findNode(nodeId) == NULL)
        return(string("Error: node ") + to_string(nodeId) + string(" not found"));
    
    circuit.findNode(nodeId)->unsetV();
    
    string success;
    ss << "Unset: the solver will determine the voltage of node " << nodeId;
    getline (ss, success);
    return(success);
}
string solve(NodeList & circuit){
    if(circuit.noNodesSetV())
        return("Error: no nodes have their voltage set");
    
    cout << "Solve: ";
    circuit.solve();
    return("");
}

bool checkStreamErrors(stringstream & stream){
    //checks for triggered stream flags
    if(stream.fail() || ((stream.peek() != ' ') && !stream.eof())){
        stream.clear();
        stream.ignore(1000, '\n');
        return true;
    }
    else return false;
}

bool checkNameAll(string name){
    if(name == "all")
        return true;
    
    return false;
}
bool checkResistance(double resistance){
    //ensure resistance is zero or positive
    if (resistance < 0)
        return true;
    
    else return false;
}
bool validInt(stringstream & stream){
    //check for parsing error that happens when an int is followed directly by another character
    if (stream.peek() == '.' || stream.peek() == 'e')       
        return true;
    
    else return false;
}
bool biggerThanZero(int a){
	if(a <= 0) return false;
	else return true;
}

string insertRSuccess(string name, double resistance, int nodeId[2], NodeList & circuit){
    
    //check if first node connection exists
    //if no, create it
    Node* temp = circuit.findOrInsert(nodeId[0]);
    
    //add the resistor to that node (in order biggest to smallest by resistance)
    temp->insertResistor(name, resistance, nodeId);
    
    //check if second node connection exists
    //if no, create it
    temp = circuit.findOrInsert(nodeId[1]);
    
    //add the resistor to that node (same as above)
    temp->insertResistor(name, resistance, nodeId);
    
    //concatenate and return success message
    string success;
    stringstream ss;
    ss << "Inserted: resistor " << name << " " << fixed << setprecision(2) << resistance
    << " Ohms " << nodeId[0] << " -> " << nodeId[1];
    getline (ss, success);
    return(success);
}
string modifyRSuccess(string name, double resistance, NodeList & circuit){
    double oldRes = circuit.modifyR(name, resistance);
    
    //concatenate and return success message
    string success;
    stringstream ss;
    ss << "Modified: resistor " << name << " from " <<fixed << setprecision(2) << oldRes << " Ohms to " << fixed << setprecision(2) << resistance << " Ohms ";
    getline (ss, success);
    return(success);
}
string printRSuccess(string name, NodeList & circuit){
    //get pointer to relevant resistor
    
    cout << "Print:" << endl;
    //print resistor info
    circuit.findRes(name)->print();
    
    return(""); //required return for command reader to work
}
string printRSuccessAll(NodeList & circuit){
    
    cout << "Print:";
    //iterate through and print all resistors
    
    return(""); //required return for command reader to work
}
string printNodeSuccess(int nodeId, NodeList & circuit){
    Node* temp = circuit.findNode(nodeId);
    
    //print node
    cout << "Print:" << endl;
    temp->print();
    return(""); //required return for command reader to work
}
string printNodeSuccessAll(NodeList & circuit){
    
    //run through list and print each node
    cout << "Print:" << endl;
    circuit.printAll();
    
    return(""); //required return for command reader to work
}
string deleteRSuccessAll(NodeList & circuit){
    
    circuit.deleteAll();
    
    return("Deleted: all resistors");
}

string deleteRSuccess(NodeList & circuit, string name){
    //get pointer to one of resistors with name
    Resistor* res1 = circuit.findRes(name);
    int endpoints [2];
    endpoints[0] = res1->getEndpointOne();
    endpoints[1] = res1->getEndpointTwo();
    Node* first = circuit.findNode(endpoints[0]);
    Node* second = circuit.findNode(endpoints[1]);
    first->removeResistor(name);
    second->removeResistor(name);
    
    return(string("Deleted: resistor ") + name);
}
