#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "Rparser.h" //function declarations used in this file

using namespace std;

string maxVal(stringstream & stream, struct Circuit & circuit){
    //initialize required maxVal variables
    int maxNodeNumber, maxResistors;
    
    //check for invalid inputs and return appropriate error message
	stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    //parse maxNodeNumber
    stream >> maxNodeNumber;
    if(checkStreamErrors(stream)){
        return("Error: invalid argument");
    }
    else if (validInt(stream)){
        return("Error: invalid argument");
    }
    else if (!biggerThanZero(maxNodeNumber)){
	    return("Error: maxVal arguments must be greater than 0");
	}
	stream >> ws;
	if (stream.eof()) 
        return("Error: too few arguments");
    
    //parse maxResistors
    stream >> maxResistors;
    if(checkStreamErrors(stream)){
        return("Error: invalid argument");
    }
    else if (validInt(stream)){
        return("Error: invalid argument");
    }
    else if (!biggerThanZero(maxResistors)){
	    return("Error: maxVal arguments must be greater than 0");
	}
	stream >> ws;
    if (!stream.eof())
        return("Error: too many arguments");
    
    //if no initial parsing errors: proceed with backend update and return success message
    return(maxValSuccess(maxNodeNumber, maxResistors, circuit));
}

string insertR(stringstream & stream, Circuit & circuit){
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
    else if (checkNodeRange(nodeId[0], circuit)){
            string nodeOutOfBounds;
            stringstream ss;
            ss << "Error: node " << nodeId[0] << " is out of permitted range " << 0 << "-" << (circuit.maxNodes);
            getline(ss,nodeOutOfBounds);
            return(nodeOutOfBounds);
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
    else if (checkNodeRange(nodeId[1], circuit)){
        string nodeOutOfBounds;
        stringstream ss;
        ss << "Error: node " << nodeId[1] << " is out of permitted range " << 0 << "-" << (circuit.maxNodes);
        getline(ss,nodeOutOfBounds);
        return(nodeOutOfBounds);
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

string modifyR(stringstream & stream, Circuit & circuit){    
    
    //initialize required modifyR variables
    string name;
    double resistance;
    int resIndex = 0;

    stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    
    //parse name
    stream >> name;
    if(checkStreamErrors(stream))       
        return("Error: invalid argument");
    else if (checkNameAll(name))
        return("Error: resistor name cannot be the keyword \"all\"");
    stream >> ws;
    if (stream.eof())
        return("Error: too few arguments");
    
    //lookup resistor index with matching name
    if (findNameIndex(name, circuit) == -1){
        stringstream ss;
        ss << "Error: resistor " << name << " not found";
        string message;
        getline(ss, message);
        return(message);
    }
    else resIndex = findNameIndex(name, circuit);
    
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
    return(modifyRSuccess(name, resistance, resIndex, circuit));
}

string printR(stringstream & stream, Circuit & circuit){    
    
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
    
    //if no initial parsing errors: proceed with print and return success message
    return(printRSuccess(name, circuit));
}

string printNode(stringstream & stream, Circuit & circuit){    
    
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
        stream.clear();
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
    if (checkNodeRange(nodeId, circuit)){
            string nodeOutOfBounds;
            ss << "Error: node " << nodeId << " is out of permitted range " << 0 << "-" << (circuit.maxNodes);
            getline(ss,nodeOutOfBounds);
            return(nodeOutOfBounds);
    }
    else if (!stream.eof())
        return("Error: too many arguments");
    
    //if no initial parsing errors: proceed with print and return success message
    return(printNodeSuccess(nodeId, circuit));
}

string deleteR(stringstream & stream, Circuit & circuit){    
    
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
    else return("Error: invalid argument");
    
    //this is for a hypothetical call to delete just a single resistor
    //else return(deleteRSuccess(circuit, name));
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
    if (name == "all")
        return true;
    
    else return false;
}
bool checkNodeRange(int node, const Circuit & circuit){
    //check if node is within range set by maxVal
    if ((node < 0) || (node > (circuit.maxNodes))) {
        return true;
    }
    else return false;
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

int findNameIndex(string name, const Circuit & circuit){
    int resIndex = -1;  //set to negative incase name is not found
    
    //for loop checks through all resistors to find name match
    for(int i = 0; i < circuit.resistorIndex; i++){
        if(name == circuit.resistorHolder[i]->getName()){
            resIndex = i;
            break;
        }
    }
    
    //returns the index in resistorHolder of the resistor with the matching name
    //returns -1 if it can't be found
    return(resIndex);
}

bool insertRFinalErrors(string & error, string name, int nodeId[2], const Circuit & circuit){
    stringstream ss;
    
    //check if resistor array is full
    if(circuit.resistorIndex == circuit.maxResistors){
        error = "Error: resistor array is full";
        return(true);
    }
    
    //check if node is full
    else if(!circuit.nodeHolder[nodeId[0]].canAddResistor(circuit.resistorIndex)){
        error = "Error: node is full";
        return(true);
    }
    else if(!circuit.nodeHolder[nodeId[1]].canAddResistor(circuit.resistorIndex)){
        error = "Error: node is full";
        return(true);
    }
    
    //check if name is already used
    else if(findNameIndex(name, circuit) != -1){
        ss << "Error: resistor " <<  name << " already exists";
        getline(ss, error);
        return(true);
    }
    
    //check if trying to connect to same node
    else if(nodeId[0] == nodeId[1]){
        ss << "Error: both terminals of resistor connect to node " << nodeId[0];
        getline(ss, error);
        return(true);
    }
    
    //return false if no error is found
    else return(false);
}

void deleteCircuit(Circuit & circuit){  //deletes entire circuit
    //delete array of Nodes
    delete [] circuit.nodeHolder;
    
    //delete individual Resistors
    for(int i = circuit.resistorIndex-1; i >= 0; i--){
        delete circuit.resistorHolder[i];
    }
    
    //delete pointers to Resistors held in circuit.resistorHolder
    delete [] circuit.resistorHolder;
    circuit.resistorHolder = NULL;
    
    //reset rest of struct circuit
    circuit.resistorIndex = 0;
    circuit.maxNodes = 0;
    circuit.maxResistors = 0;
}

void deleteResistor(Circuit & circuit, int rIndex){ //deletes a single resistor
    int* nodeIDs;
    
    //clear resistor's associated node references
    nodeIDs = circuit.resistorHolder[rIndex]->getNodeReferences();
    circuit.nodeHolder[nodeIDs[0]].removeResistor(rIndex);
    circuit.nodeHolder[nodeIDs[1]].removeResistor(rIndex);
    
    //delete Resistor
    delete circuit.resistorHolder[rIndex];
    circuit.resistorHolder[rIndex] = NULL;
    
    //update rest of struct circuit
    circuit.resistorIndex--;
}

string maxValSuccess(int maxNode, int maxRes, Circuit & circuit){
    //check for maxVal errors
    if(!biggerThanZero(maxNode))
        return("Error: maxVal arguments must be greater than 0");
    if(!biggerThanZero(maxRes))
        return("Error: maxVal arguments must be greater than 0");
    
    //if circuit has already been set, clear circuit in preperation for setting new size
     if(circuit.hasBeenSet){
         deleteCircuit(circuit);
     }
     else circuit.hasBeenSet = true;
    
    //allocate new circuit element sizes
    circuit.nodeHolder = new Node[maxNode+1];
    circuit.resistorHolder = new Resistor*[maxRes+1];
    
    //initialize rest of circuit members to correct values
    circuit.maxNodes = maxNode;
    circuit.maxResistors = maxRes;
    circuit.resistorIndex = 0;
    
    //concatenate and return success message
    string success;
    stringstream ss;
    ss << "New network: max node number is " << maxNode <<  "; max resistors is " << maxRes;
    getline(ss, success);
    return(success);
}

string insertRSuccess(string name, double resistance, int nodeId[2], Circuit & circuit){
    //check for errors
    string error;
    if(insertRFinalErrors(error, name, nodeId, circuit))
        return(error);
    
    //initialize new Resistor and store it in the array resistorHolder
    circuit.resistorHolder[circuit.resistorIndex] = new Resistor(circuit.resistorIndex, name, resistance, nodeId);
    
    //update relevant Node's fields with new resistor
    circuit.nodeHolder[nodeId[0]].addResistor(circuit.resistorIndex);
    circuit.nodeHolder[nodeId[1]].addResistor(circuit.resistorIndex);
    
    circuit.resistorIndex++;
    
    //concatenate and return success message
    string success;
    stringstream ss;
    ss << "Inserted: resistor " << name << " " << fixed << setprecision(2) << resistance
    << " Ohms " << nodeId[0] << " -> " << nodeId[1];
    getline (ss, success);
    return(success);
}
string modifyRSuccess(string name, double resistance, int resIndex, Circuit & circuit){
    //modify the appropriate Resistor's resistance value
    double res = circuit.resistorHolder[resIndex]->getResistance();
    circuit.resistorHolder[resIndex]->setResistance(resistance);
    
    //concatenate and return success message
    string success;
    stringstream ss;
    ss << "Modified: resistor " << name << " from " <<fixed << setprecision(2) << res << " Ohms to " << fixed << setprecision(2) << resistance << " Ohms ";
    getline (ss, success);
    return(success);
}
string printRSuccess(string name, const Circuit & circuit){
    //check if resistor is found
    int nameIndex = findNameIndex(name, circuit);
    
    //if resistor isn't found, print error message
    if(nameIndex == -1){
        stringstream ss;
        ss << "Error: resistor " << name << " not found";
        string error;
        getline(ss, error);
        return(error);
    }
    
    //print info for corresponding resistor
    cout << "Print:" << endl;
    circuit.resistorHolder[nameIndex]->print();
    return(""); //required return for command reader to work
}
string printRSuccessAll(const Circuit & circuit){
    //iterate through resistorHolder array and print each resistor
    cout << "Print:";
    for(int i = 0; i < circuit.resistorIndex; i++){
        cout << endl;
        circuit.resistorHolder[i]->print();
    }
    return(""); //required return for command reader to work
}
string printNodeSuccess(int nodeId, const Circuit & circuit){
    //check if the nodeId is out of range
    if (checkNodeRange(nodeId, circuit)){
        string nodeOutOfBounds;
        stringstream ss;
        ss << "Error: node " << nodeId << " is out of permitted range " << 0 << "-" << (circuit.maxNodes);
        getline(ss,nodeOutOfBounds);
        return(nodeOutOfBounds);
    }
    
    //print node if it's within range
    cout << "Print:" << endl;
    circuit.nodeHolder[nodeId].print(nodeId);
    for(int i = 0; i < circuit.nodeHolder[nodeId].getNumRes(); i++){
        cout << endl << "  ";
        circuit.resistorHolder[circuit.nodeHolder[nodeId].getResIDArray(i)]->print();
    }
    
    return(""); //required return for command reader to work
}
string printNodeSuccessAll(const Circuit & circuit){
    //iterate through nodeHolder array and print each node
    cout << "Print:";
    for(int i = 0; i <= circuit.maxNodes; i++){
        cout << endl;
        circuit.nodeHolder[i].print(i);
        
        //print output message for each resisitor in the node
        for(int j = 0; j < circuit.nodeHolder[i].getNumRes(); j++){
            cout << endl << "  ";
            circuit.resistorHolder[circuit.nodeHolder[i].getResIDArray(j)]->print();
        }
    }
    
    return(""); //required return for command reader to work
}
string deleteRSuccessAll(Circuit & circuit){
    //cycles through resistorHOlder array and deletes any existing Resistors
    for(int i = circuit.resistorIndex-1; i >= 0; i--){
        if(circuit.resistorHolder[i] != NULL)
            deleteResistor(circuit, i);
    }
    
    //concatenate and return success message
    string success;
    stringstream ss;
    ss << "Deleted: all resistors";
    getline (ss, success);
    
    return(success);
}

string deleteRSuccess(Circuit & circuit, string name){  //unnecessary for this lab, just personal addition
    
    //deletes a single reisistor
    deleteResistor(circuit, findNameIndex(name, circuit));
    
    //concatenate and return success message
    string success;
    stringstream ss;
    ss << "Deleted: resistor " << name;
    getline (ss, success);
    
    return(success);
}
