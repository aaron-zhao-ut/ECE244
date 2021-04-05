#ifndef _TREEDB_H
#define _TREEDB_H

#include "TreeNode.h"
#include "DBentry.h"

class TreeDB {

private:
   TreeNode* root;
   int probesCount;
    
   // additional private functions:
    
    // private function that returns the leaf that a potential name should be attached to
    TreeNode* traverseToLeaf(TreeNode*, string);
    
    //returns a pointer to the node above the one holding the matching key
    TreeNode* traverseToPointer(TreeNode*, string);
    
    //finds the largest node in a subtree, disconnects it from the tree and returns it
    TreeNode* removeLargest(TreeNode*);
    
    //recursive implementation of find
    DBentry* findHelper(TreeNode*, string);
    
    // recursively walks through tree and prints each node
    void printHelper(TreeNode*);
    
    //recursively traverse entire tree, adding one to return value if the node is active
    int traverseEntireTree(TreeNode*) const;
    
    // recursively walks through tree and deletes each node
    void removeAll(TreeNode*);
    
public:
    // the default constructor, creates an empty database.
    TreeDB();

   // the destructor, deletes all the entries in the database.
   ~TreeDB();

   // inserts the entry pointed to by newEntry into the database.
   // If an entry with the same key as newEntry's exists
   // in the database, it returns false. Otherwise, it returns true.
   bool insert(DBentry* newEntry);

   // searches the database for an entry with a key equal to name.
   // If the entry is found, a pointer to it is returned.
   // If the entry is not found, the NULL pointer is returned.
   // Also sets probesCount
   DBentry* find(string name);

   // deletes the entry with the specified name (key)  from the database.
   // If the entry was indeed in the database, it returns true.
   // Returns false otherwise.
   bool remove(string name);
	
   // deletes all the entries in the database.
   void clear();
    
   // prints the number of probes stored in probesCount
   void printProbes() const;
   
   // computes and prints out the total number of active entries
   // in the database (i.e. entries with active==true).
   void countActive () const;

   // Prints the entire tree, in ascending order of key/name
   friend ostream& operator<< (ostream& out, TreeDB& rhs);
}; 

ostream& operator<< (ostream& out, TreeDB& rhs);

#endif
