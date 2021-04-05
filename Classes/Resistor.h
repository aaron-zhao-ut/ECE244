#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Resistor
{
private:
   double resistance=0.0; // resistance (in Ohms)
   string name; // C++ string holding the label
   int endpointNodeIDs[2]; // IDs of nodes it attaches to
   int rIndex; // it's index in circuit.resistorHolder

public:
    Resistor(int rIndex_,string name_,double resistance_,int endpoints_[2]);
    // rIndex_ is the index of this resistor in the resistor array
    // endpoints_ holds the node indices to which this resistor connects

    ~Resistor();
    
    
    string getName() const;       // returns the name
    double getResistance() const; // returns the resistance
    int* getNodeReferences();     // returns nodeIDs

    //error check then sets resistance to resistance_
    void setResistance (double resistance_);
    
    //prints a resistor according to format guidelines
    void print();
    
    //not using this function
    friend ostream& operator<<(ostream&,const Resistor&);
};

ostream& operator<<(ostream&,const Resistor&);

#endif	/* RESISTOR_H */
