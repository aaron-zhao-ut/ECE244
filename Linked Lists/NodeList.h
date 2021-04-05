#ifndef NodeList_h
#define NodeList_h
#include "Node.h"
#include "Resistor.h"
#include <math.h>
#define MIN_ITERATION_CHANGE 0.0001

using namespace std;

class NodeList
{
private:
    //head of a linked list of Nodes
    Node* head = NULL;
public:
    NodeList();
    NodeList(const NodeList& other);
    ~NodeList();
    
    Node* findOrInsert(int);
    Node* findNode(int);
    Node* findNodeVCanChange();
    bool noNodesSetV();
    void deleteNode(Node*);
    void deleteAll();
    Resistor* findRes(string)const;
    bool resExists(string);
    
    
    double modifyR(string, double);
    double voltageCalc(Node*);
    
    void solve();
    void print(int);
    void printAll() const;
};


#endif /* NodeList_h */
