#include "Node.h"

Node::Node(int ID){
    nodeId = ID;
    fixedVoltage = false;
    next = NULL;
    voltage = 0;
    prevVoltage = 0;
}
Node::~Node(){
    resList.deleteAllResistors();
}

void Node::removeResistor(string name_){
    
    //check if resistor being deleted is attached to this node
    Resistor* temp;
    temp = findRes(name_);
    
    //if its not, return
    if(temp == NULL){
        return;
    }
    else
        resList.deleteResistorByName(name_);
}
void Node::insertResistor(string name, double resistance, int nodeID [2]){
    resList.insertResistor(name, resistance, nodeID);
}

Resistor* Node::findResByIndex(int index){
    return(resList.findResByIndex(index));
}
int Node::getID()const{
    return(nodeId);
}

int Node::getNumRes()const{
    return(resList.getNumOfResistors());
}

void Node::setV(double voltage_){
    voltage = voltage_;
    fixedVoltage = true;
}

void Node::unsetV(){
    voltage = 0;
    fixedVoltage = false;
}
bool Node::isFixed(){
    return(fixedVoltage);
}

Node* Node::getNext(){
    return(next);
}
void Node::setNext(Node* next_){
    next = next_;
}

double Node::getVoltage() const{
    return(voltage);
}
double Node::getPrevVoltage() const{
    return(prevVoltage);
}
void Node::updateVoltage(double newVolts){
    prevVoltage = voltage;
    voltage = newVolts;
}

Resistor* Node::findRes(string name){
    return(resList.findRes(name));
}
bool Node::resExists(string name){
    return(resList.resistorExists(name));
}

double Node::calcPreCoefficient() const{
    return(resList.calcPreCoefficient());
}

void Node::modifyAndSort(string name, double resistance){
    resList.modifyAndSort(name, resistance);
}

void Node::print(){
    cout << "Connections at node " << nodeId << ": " << getNumRes() << " resistor(s)" << endl;
    resList.printAll();
}
