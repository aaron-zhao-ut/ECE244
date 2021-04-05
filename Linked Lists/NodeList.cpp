#include "NodeList.h"


NodeList::NodeList(){}
NodeList::NodeList(const NodeList & other){}
NodeList::~NodeList(){}

void NodeList::solve(){
    Node* current = head;
    Node* endNode = findNodeVCanChange();
    endNode->updateVoltage(1);
    while(fabs((endNode->getVoltage() - endNode->getPrevVoltage())) >= MIN_ITERATION_CHANGE){
        while(current!=NULL){
            if(!current->isFixed()){
                current->updateVoltage(voltageCalc(current));
            }
            current = current->getNext();
        }
        current = head;
    }
    current = head;
    while(current != NULL){
        cout << endl << "  Node " << current->getID() << ": " << fixed << setprecision(2) <<current->getVoltage() << " V";
        current = current->getNext();
    }
}

double NodeList::voltageCalc(Node* operee){
    Resistor* temp;
    int numOfRes = operee->getNumRes();
    int otherEndpoint;
    double coefficient, currents = 0;
    coefficient = 1/operee->calcPreCoefficient();
    for(int i = 0; i < numOfRes; i++){
        temp = operee->findResByIndex(i);
        if(temp->getEndpointOne()!=operee->getID()){
            otherEndpoint = temp->getEndpointOne();
        }
        else otherEndpoint = temp->getEndpointTwo();
        currents += (findNode(otherEndpoint)->getVoltage()/temp->getResistance());
    }
    
    return(coefficient * currents);
    
}
bool NodeList::noNodesSetV(){
    Node* current = head;
    while (current != NULL){
        if(current->isFixed()){
            return false;
        }
    }
    return true;
}

Node* NodeList::findNodeVCanChange(){
    Node* current = head;
    while(head != NULL){
        if(!current->isFixed())
            return(current);
        current=current->getNext();
    }
    return NULL;
}

Node* NodeList::findOrInsert(int nodeId){
    //check if node exists
    Node* current = head;
    
    //insert at head if smallest
    if(current==NULL){
        current = new Node(nodeId);
        current->setNext(head);
        head = current;
        return(head);
    }
    else if(head->getID() > nodeId){
        current = new Node(nodeId);
        current->setNext(head);
        head = current;
        return(head);
    }
    else if (current->getNext() == NULL){
        Node* temp = new Node(nodeId);
        temp->setNext(current->getNext());
        current->setNext(temp);
        return(temp);
    }
    while(current != NULL){
        if(current->getID()==nodeId)
            return(current);
        else if(current->getID() < nodeId){
            if (current->getNext() == NULL){
                Node* temp = new Node(nodeId);
                temp->setNext(current->getNext());
                current->setNext(temp);
                return(temp);
            }
            else if((current->getNext()->getID() > nodeId)){
                Node* temp = new Node(nodeId);
                temp->setNext(current->getNext());
                current->setNext(temp);
                return(temp);
            }
        }
        current=current->getNext();
    }
    return(NULL);
}
Node* NodeList::findNode(int nodeID){
    Node* current = head;
    
    while(current!=NULL){
        if(current->getID() == nodeID)
            return(current);
        current = current->getNext();
    }
    return(NULL);   //if node isn't found
}

void NodeList::deleteNode(Node* nodeToDel){
    Node* current = head;
    if(current == NULL)
        return;
    
    if(current == nodeToDel){
        head = current->getNext();
        delete current;
        return;
    }
    
    while(current != NULL){
        if(current->getNext() == nodeToDel){
            Node* temp = current;
            current = current->getNext();
            temp->setNext(current->getNext());
            delete current;
            return;
        }
        current = current->getNext();
    }
}
void NodeList::deleteAll(){
    Node* current = head;
    while(current!=NULL){
        head = current->getNext();
        delete current;
        current = head;
    }
}

double NodeList::modifyR(string name, double resistance){
    Node* current = head;
    Resistor* old;
    bool oldResFound = false;
    double oldRes = 0;
    while(current != NULL){
        if(current->resExists(name)&& !oldResFound){
            old = current->findRes(name);
            oldRes = old->getResistance();
            oldResFound = true;
        }
        current->modifyAndSort(name, resistance);
        current = current->getNext();
    }
    return (oldRes);
}

Resistor* NodeList::findRes(string name)const{
    Node* current = head;
    while(current!=NULL){
        if(current->resExists(name)){
            return(current->findRes(name));
        }
        current = current->getNext();
    }
    return NULL;
}
bool NodeList::resExists(string name){
    Node* current = head;
    while(current!=NULL){
        if(current->resExists(name)){
            return(true);
        }
        current = current->getNext();
    }
    return false;
}

void NodeList::print(int nodeId){
    Node* temp = findNode(nodeId);
    temp->print();
}
void NodeList::printAll()const{
    Node* current = head;
    while(current!=NULL){
        current->print();
        current=current->getNext();
    }
}







