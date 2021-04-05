#ifndef ResistorList_h
#define ResistorList_h

#include "Resistor.h"
using namespace std;

class ResistorList
{
private:
    //pointer to the first resistor at a Node;
    Resistor* head;
    int numOfResistors;
    bool isEmpty;

public:
    ResistorList();
    ResistorList(const ResistorList& other);
    ~ResistorList();
    
    void insertResistor(string, double, int[2]);
    void deleteResistor(Resistor*);
    void deleteResistorByName(string);
    void deleteAllResistors();
    void setIsEmpty();
    
    double calcPreCoefficient()const;
    
    


    
    Resistor* getHead()const;
    void setHead(Resistor* temp);
    int getNumOfResistors()const;
    bool getIsEmpty()const;
    
    
    bool resistorExists(string) const;
    Resistor* findRes(string);
    Resistor* findResByIndex(int);
    
    void modifyAndSort(string, double);
    
    //I think this should return the old resistance for the print message
    //must also resort the node
    double modifyResistance(double);
    
    void print(string) ;
    void printAll() const;
};

#endif /* ResistorList_h */
