#include "TreeDB.h"

// the default constructor, creates an empty database.
TreeDB::TreeDB(){
    root = NULL;
    probesCount = 0;
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB(){
    clear();
}

// inserts the entry pointed to by newEntry into the database.
// If an entry with the same key as newEntry's exists
// in the database, it returns false. Otherwise, it returns true.
bool TreeDB::insert(DBentry* newEntry){
    //circuit is empty case
    if(root == NULL){
        root = new TreeNode(newEntry);
        return true;
    }
    
    //check for duplicates
    if (find(newEntry->getName()) != NULL)
        return false;
    
    //get node to attach it to
    TreeNode * attachTo = traverseToLeaf(root, newEntry->getName());
    
    //attach node
    if(newEntry->getName() < attachTo->getEntry()->getName())
        attachTo->setLeft(new TreeNode(newEntry));
    
    else if(newEntry->getName() > attachTo->getEntry()->getName())
        attachTo->setRight(new TreeNode(newEntry));
    
    //return true for success
    return true;
}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount
DBentry* TreeDB::find(string name){
    probesCount = 0;
    return(findHelper(root, name));
}

// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
bool TreeDB::remove(string name){
    //empty circuit case
    if(root == NULL)
        return false;
    //if node doesn't exist in the database
    else if (find(name)==NULL)
        return false;
    
    
    TreeNode* newHead;
    TreeNode* nodeToDelete;
    bool isLeft, isHead = false;
    
    //initialize remove process if deleting top level node
    if(root->getEntry()->getName() == name){
        isHead = true;
        isLeft = true;
        newHead = new TreeNode(new DBentry());
        nodeToDelete = root;
        newHead->setLeft(root);
    }
    else{   //initialize remove process for other nodes
        newHead = traverseToPointer(root, name);
    
        if(newHead->getLeft()->getEntry()->getName() == name){
            nodeToDelete = newHead->getLeft();
            isLeft = true;
        }
        else{
            nodeToDelete = newHead->getRight();
            isLeft = false;
        }
    }
    if(nodeToDelete->getLeft() == NULL){
        if(nodeToDelete->getRight() == NULL){//deleting a leaf
            if(isLeft)
                newHead->setLeft(NULL);
            else
                newHead->setRight(NULL);
        }
        else{
            //it is a one branched subtree with the branch to the right
            if(isLeft)
                newHead->setLeft(nodeToDelete->getRight());
            else
                newHead->setRight(nodeToDelete->getRight());
        }
        if(isHead){
            root = nodeToDelete->getRight();
            delete newHead;
            newHead = NULL;
        }
        delete nodeToDelete;
    }
    else if(nodeToDelete->getRight() == NULL){
        //it is a one branched subtree with the branch to the left
        if(isLeft)
            newHead->setLeft(nodeToDelete->getLeft());
        else
            newHead->setRight(nodeToDelete->getLeft());
        if(isHead){
            root = nodeToDelete->getLeft();
            delete newHead;
            newHead = NULL;
        }
        delete nodeToDelete;
    }
    else{
        //its got a full subtree
        //find largest node in left subtree
        if(nodeToDelete->getLeft()->getRight() == NULL){
            if(isLeft)
                newHead->setLeft(nodeToDelete->getLeft());
            else
                newHead->setRight(nodeToDelete->getLeft());
            
            nodeToDelete->getLeft()->setRight(nodeToDelete->getRight());
            if(isHead){
                root = nodeToDelete->getLeft();
                delete newHead;
                newHead = NULL;
            }
            delete nodeToDelete;
        }
        else{
            TreeNode* temp = removeLargest(nodeToDelete->getLeft());
            if(isLeft)
                newHead->setLeft(temp);
            else
                newHead->setRight(temp);
            
            if(isHead){
                root = temp;
                delete newHead;
                newHead = NULL;
            }
            
            //attach in place of nodeToDelete
            temp->setLeft(nodeToDelete->getLeft());
            temp->setRight(nodeToDelete->getRight());
            delete nodeToDelete;
        
        }
        
    }
    
    return true;
}

// deletes all the entries in the database.
void TreeDB::clear(){
    removeAll(root);
    root = NULL;
}

// prints the number of probes stored in probesCount
void TreeDB::printProbes() const{
    cout << probesCount << endl;
}

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive () const{
    cout << traverseEntireTree(root) << endl;
}

// private function that returns the leaf that a potential name should be attached to
TreeNode* TreeDB::traverseToLeaf(TreeNode* current, string key){
    
    //traverse left tree
    if(current->getEntry()->getName() > key){
        if(current->getLeft() == NULL)
            return(current);
        else
            return(traverseToLeaf(current->getLeft(), key));
    }
    
    //else traverse right tree
    else if(current->getEntry()->getName() < key){
        if(current->getRight() == NULL)
            return(current);
        else
            return(traverseToLeaf(current->getRight(), key));
    }
    
    //return NULL if key is found
    return NULL;
}

//returns a pointer to the node above the one holding the matching key
TreeNode* TreeDB::traverseToPointer(TreeNode* current, string key){
    
    //traverse left tree
    if(current->getEntry()->getName() > key){
        if(current->getLeft()->getEntry()->getName() == key)
            return(current);
        else
            return(traverseToPointer(current->getLeft(), key));
    }
    
    //else traverse right tree
    else if(current->getEntry()->getName() < key){
        if(current->getRight()->getEntry()->getName() == key)
            return(current);
        else
            return(traverseToPointer(current->getRight(), key));
    }
    
    //returns null if key is not found
    return NULL;
}

//finds the largest node in a subtree, disconnects it from the tree and returns it
TreeNode* TreeDB::removeLargest(TreeNode * current){
    if(current->getRight()->getRight() == NULL){
        TreeNode* temp = current->getRight();
        
        if(temp->getLeft() != NULL)
            current->setRight(temp->getLeft());
        
        else
            current->setRight(NULL);
        temp->setLeft(NULL);
        temp->setRight(NULL);
        return(temp);
    }
    
    else
        removeLargest(current->getRight());
    
    return NULL;
}

//recursive implementation of find
DBentry* TreeDB::findHelper(TreeNode* probe, string name){
    if(root == NULL)
        return NULL;
    if(probe == NULL)
        return NULL;
    
    probesCount++;
    if(probe->getEntry()->getName() == name)
        return(probe->getEntry());
    
    else if(probe->getEntry()->getName() > name){
        return(findHelper(probe->getLeft(), name));
    }
    else
        return(findHelper(probe->getRight(), name));
}

// recursively walks through tree and prints each node
void TreeDB::printHelper(TreeNode* current){
    if(current == NULL)
        return;
    else{
        printHelper(current->getLeft());
        cout << *current->getEntry() << endl;
        printHelper(current->getRight());
        return;
    }
}

//recursively traverse entire tree, adding one to return value if the node is active
int TreeDB::traverseEntireTree(TreeNode * current) const{
    if(current == NULL){
        return 0;
    }
    else if(current->getEntry()->getActive())   //add one if node is active
        return(traverseEntireTree(current->getLeft())+traverseEntireTree(current->getRight()) + 1);
    else    //otherwise keep going
        return(traverseEntireTree(current->getLeft())+traverseEntireTree(current->getRight()));
}

// recursively walks through tree and deletes each node
void TreeDB::removeAll(TreeNode* current){
    //base case
    if(current == NULL)
        return;
    
    //recursively move down the tree
    removeAll(current->getLeft());
    current->setLeft(NULL);
    removeAll(current->getRight());
    current->setRight(NULL);
    
    //delete the node
    delete current;
    current = NULL;
    return;
}

// Prints the entire tree, in ascending order of key/name
ostream& operator<< (ostream& out, TreeDB& rhs){
    rhs.printHelper(rhs.root);
    return(out);
}
