#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "ResistorList.h"
using namespace std;

class Node
{
private:

    int nodeId;
    double voltage;
    double prevVoltage;
    bool fixedVoltage;
    
    ResistorList resList;
    Node* next;

public:
   Node(int);
   ~Node();

   //Remove a resistor from this node.
   void removeResistor(string);

    int getID()const;
    Node* getNext();
    void setNext(Node* next_);
    void setV(double);
    void unsetV();
    bool isFixed();
    Resistor* findResByIndex(int);

    
    double calcPreCoefficient()const;
    
    double getVoltage() const;
    double getPrevVoltage() const;
    void updateVoltage(double);

    bool resExists(string);

    void insertResistor(string, double, int[2]);
    
    void modifyAndSort(string, double);
    
    //returns the number of attached resistors. 0 if there are none
    int getNumRes()const;
    //looks for a resistor by name, returns NULL if not found
    Resistor* findRes(string);

   // prints the whole node
   void print ();

};

#endif	/* NODE_H */
