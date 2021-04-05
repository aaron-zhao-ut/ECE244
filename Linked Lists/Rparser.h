#ifndef RPARSER_H
#define RPARSER_H

using namespace std;

#include "Resistor.h"
#include "Node.h"
#include "NodeList.h"
#include "ResistorList.h"

//individual command's parsers. Parses input stream for errors, calls function to perform backend
//and returns error/success message to be printed to screen

//string maxVal(stringstream &, NodeList &);
string insertR(stringstream & , NodeList &);
string modifyR(stringstream & , NodeList &);
string printR(stringstream & , NodeList &);
string printNode(stringstream & , NodeList &);
string deleteR(stringstream & , NodeList &);
string setV(stringstream & , NodeList &);
string unsetV(stringstream & , NodeList &);
string solve(NodeList &);


//error checking functions that are used by the parse functions above. They perform small tasked
//that are often repeated

//checks stream for flags and resets them if necessary
bool checkStreamErrors(stringstream &);

//Check by name if resistor is already in circuit. Recursive.
bool checkResistorExists(string, const NodeList &);
bool checkNodeExists(int, const NodeList &);

//checks for name "all"
bool checkNameAll(string); //need to write this!

//checks for negative resistance
bool checkResistance(double);

//checks for characters trailing an int that the in-stream doesn't automatically pickup
bool validInt(stringstream &);

 //checks that maxVal inputs are bigger than 0
bool biggerThanZero(int a);



//functions that perform backend error checking or execute a backend operation such as deleteR

//deletes all content stored within nodeHolder and resistorHolder
void deleteCircuit(NodeList&);

//deletes a single Resistor including it's references stored in Nodes
void deleteResistor(NodeList &, int rIndex);



//if stream is parsed, manages backend execution and if successful
//will return success message

string insertRSuccess(string , double , int [2], NodeList &);
string modifyRSuccess(string , double , NodeList &);
string printRSuccess(string ,  NodeList &);
string printRSuccessAll(NodeList &);
string printNodeSuccess(int,  NodeList &);
string printNodeSuccessAll(NodeList &);
string deleteRSuccessAll(NodeList &);
string deleteRSuccess(NodeList &, string);   //unneccessary but added for testing


#endif /* PARSER_H */
