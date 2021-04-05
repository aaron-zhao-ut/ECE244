#include "ResistorList.h"

ResistorList::ResistorList(){
    isEmpty = true;
    numOfResistors = 0;
    head = NULL;
}
ResistorList::ResistorList(const ResistorList& other){}
ResistorList::~ResistorList(){}

Resistor* ResistorList::getHead()const{
    return(head);
}
void ResistorList::setHead(Resistor* temp){
    head = temp;
}
int ResistorList::getNumOfResistors()const{
    return (numOfResistors);
}
bool ResistorList::getIsEmpty() const{
    return(isEmpty);
}
void ResistorList::setIsEmpty(){
    if(numOfResistors==0){
        isEmpty = true;
    }
    else isEmpty=false;
}


void ResistorList::insertResistor(string name, double resistance, int nodeID [2]){
    Resistor* current = head;
    if(current==NULL){
        current = new Resistor(name, resistance, nodeID);
        numOfResistors++;
        setIsEmpty();
        current->setNext(head);
        head = current;
        return;
    }
    else if(current->getNext() == NULL){
        current->setNext(new Resistor(name, resistance, nodeID));
        numOfResistors++;
        setIsEmpty();
        return;
    }
    while(current!=NULL){
        if(current->getResistance() >= resistance){
            if(current->getNext() == NULL){
                current->setNext(new Resistor(name, resistance, nodeID));
                numOfResistors++;
                setIsEmpty();
                return;
            }
            else if(current->getNext()->getResistance() < resistance){
                Resistor* temp = new Resistor(name, resistance, nodeID);
                numOfResistors++;
                setIsEmpty();
                temp->setNext(current->getNext());
                current->setNext(temp);
                return;
            }
        }
        current=current->getNext();
    }
}

void ResistorList::deleteResistor(Resistor* resToDel){
    Resistor* current = head;
    if(current == NULL)
        return;
    if(current == resToDel){
        head = current->getNext();
        delete current;
        numOfResistors--;
        setIsEmpty();
        return;
    }
    
    while(current != NULL){
        if(current->getNext() == resToDel){
            Resistor* temp = current;
            current = current->getNext();
            temp->setNext(current->getNext());
            delete current;
            numOfResistors--;
            setIsEmpty();
            return;
        }
        current = current->getNext();
    }
    
}
void ResistorList::deleteResistorByName(string name){
    Resistor* current = head;
    if(current == NULL)
        return;
    if(current->getName() == name){
        head = current->getNext();
        delete current;
        numOfResistors--;
        setIsEmpty();
        return;
    }
    
    while(current != NULL){
        if(current->getNext()->getName() == name){
            Resistor* temp = current;
            current = current->getNext();
            temp->setNext(current->getNext());
            delete current;
            numOfResistors--;
            setIsEmpty();
            return;
        }
        current = current->getNext();

    }
    
}
void ResistorList::deleteAllResistors(){
    Resistor* current = head;
    while(current!=NULL){
        head = current->getNext();
        delete current;
        current = head;
    }
    numOfResistors=0;
    isEmpty=true;
}

bool ResistorList::resistorExists(string name) const{
    Resistor* current = head;
    while(current!=NULL){
        if(current->getName()==name)
            return true;
        current = current->getNext();
    }
    return false;
}
void ResistorList::modifyAndSort(string name, double resistance){
    if(!resistorExists(name))
        return;
    
    Resistor* current = findRes(name);
    int nodeID [2] = {current->getEndpointOne(), current->getEndpointTwo()};
    deleteResistorByName(name);
    insertResistor(name, resistance, nodeID);
    
}

Resistor* ResistorList::findRes(string name){
    Resistor* current = head;
    //search linked list for resistor with name == name_
    while(current != NULL){
        if(current->getName()==name)
            return(current);
        current=current->getNext();
    }
    return NULL;
}
Resistor* ResistorList::findResByIndex(int index){
    Resistor* current = head;
    int counter = 0;
    //search linked list for resistor with name == name_
    while(current != NULL){
        if(counter==index)
            return(current);
        current=current->getNext();
        counter++;
    }
    return NULL;
}


double ResistorList::calcPreCoefficient()const{
    Resistor* current = head;
    double preCoeff = 0;
    while(current!=NULL){
        preCoeff += 1/current->getResistance();
        current=current->getNext();
    }
    return(preCoeff);
}


void ResistorList::print(string name){
    findRes(name)->print();
}
void ResistorList::printAll() const{
    Resistor* current = head;
    
    while(current!=NULL){
        current->print();
        cout << endl;
        current = current->getNext();
    }
}







