#include "Node.h"

Node::Node(){}
Node::~Node(){}

bool Node::canAddResistor(int rIndex){
    if(numRes == MAX_RESISTORS_PER_NODE)
        return(false);
    else return(true);
}

void Node::addResistor(int rIndex){
    resIDArray[numRes] = rIndex;
    numRes++;
}

int Node::getNumRes()const{
    return(numRes);
}

int Node::getResIDArray(int i)const{
    return resIDArray[i];
}

void Node::removeResistor(int resIndex){
    int index = -1;
    
    //check if resistor being deleted is attatched to this node
    //if so find it's index in resIDArray
    for(int i = 0; i <= numRes; i++){
        if(resIDArray[i] == resIndex){
            index = i;
            break;
        }
    }
    if(index == -1)
        cout << "Node connection not Found" << endl;
    
    //remove the resistor from it's slot in resIDArray and shift remaining ones down
    for(int i = index; i < numRes; i++){
        resIDArray[index] = resIDArray[index+1];
    }
    numRes--;
}

void Node::print(int nodeIndex){
    cout << "Connections at node " << nodeIndex << ": " << numRes << " resistor(s)";
}
