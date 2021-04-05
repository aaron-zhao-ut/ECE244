#include "Resistor.h"

Resistor::Resistor(string name_, double resistance_, int endpoints_[2]){
	name = name_;
	resistance = resistance_;	
	endpoints[0] = endpoints_[0];
	endpoints[1] = endpoints_[1];
    next = NULL;
}

Resistor::~Resistor(){}

string Resistor::getName() const{ // returns the name
	return(name);
}

double Resistor::getResistance() const{ // returns the resistance
	return(resistance);
}

void Resistor::setResistance (double resistance_){	//sets the resistance of the resistor
	if(resistance_ >= 0)
		resistance = resistance_;
	else	//shouldn't ever get here, but just in case
		cout << "Error: negative resistance" << endl;
}

int* Resistor::getNodeReferences(){ // returns IDs of nodes it attaches to
    return(endpoints);
}
int Resistor::getEndpointOne()const{
    return(endpoints[0]);
}
int Resistor::getEndpointTwo()const{
    return(endpoints[1]);
}

Resistor* Resistor::getNext()const{
    return(next);
}
void Resistor::setNext(Resistor* temp){
    next = temp;
}

void Resistor::print(){ //prints a resistor according to format guidelines
    cout << "  " << setw(20) << left << name << " " << setw(8) << fixed << setprecision(2) << resistance << " Ohms " << endpoints[0] << " -> " << endpoints[1];
}
