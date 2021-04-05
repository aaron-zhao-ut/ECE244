#ifndef RPARSER_H
#define RPARSER_H

using namespace std;

#include "Resistor.h"
#include "Node.h"

//struct to hold all Nodes and Resistors of a circuit
struct Circuit
{
	Node* nodeHolder;
	Resistor** resistorHolder;
    
	int resistorIndex = 0;
	bool hasBeenSet = false;
    int maxNodes, maxResistors;
};


//individual command's parsers. Parses input stream for errors, calls function to perform backend
//and returns error/success message to be printed to screen

string maxVal(stringstream & stream, Circuit &);
string insertR(stringstream & , Circuit &);
string modifyR(stringstream & , Circuit &);
string printR(stringstream & , Circuit &);
string printNode(stringstream & , Circuit &);
string deleteR(stringstream & , Circuit &);


//error checking functions that are used by the parse functions above. They perform small tasked
//that are often repeated

//checks stream for flags and resets them if necessary
bool checkStreamErrors(stringstream &);

//checks for name "all"
bool checkNameAll(string);

//checks for negative resistance
bool checkResistance(double);

//checks for characters trailing an int that the stream doesn't automatically pickup
bool validInt(stringstream &);

 //checks that maxVal inputs are bigger than 0
bool biggerThanZero(int a);



//functions that perform backend error checking or execute a backend operation such as deleteR

//returns the index of the resistor called name
int findNameIndex(string, const Circuit &);

//ensures nodes are between 0-circuit.maxNode
bool checkNodeRange(int, const Circuit&);

//checks for final backend errors before creating a new Resistor
bool insertRFinalErrors(string&, string, int[2], const Circuit &);

//deletes all content stored within nodeHolder and resistorHolder
void deleteCircuit(Circuit&);

//deletes a single Resistor including it's references stored in Nodes
void deleteResistor(Circuit &, int rIndex);



//if stream is parsed, manages backend execution and if successful
//will return success message

string maxValSuccess(int, int, Circuit &);
string insertRSuccess(string , double , int [2], Circuit &);
string modifyRSuccess(string , double , int, Circuit &);
string printRSuccess(string , const Circuit &);
string printRSuccessAll(const Circuit &);
string printNodeSuccess(int, const Circuit &);
string printNodeSuccessAll(const Circuit &);
string deleteRSuccessAll(Circuit &);
string deleteRSuccess(Circuit &, string);   //unneccessary but added for testing


#endif /* PARSER_H */
