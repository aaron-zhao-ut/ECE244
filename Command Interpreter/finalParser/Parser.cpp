#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>

#include "Parser.h" 

#define MAX_NODE_NUMBER 5000

using namespace std;

string insertR(stringstream & stream){    
    
    
    string name;
    double resistance;
    int nodeId1, nodeId2;
    stringstream ss;
    
    stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    
    stream >> name;
    
    
    if(checkStreamErrors(stream)){
        return("Error: invalid argument");
    }

    else if (checkNameErrors(name)){
        return("Error: resistor name cannot be the keyword \"all\"");
    }
    
    else{
        stream >> ws;
        if (stream.eof()) 
            return("Error: too few arguments");
        
        stream >> resistance;
        
        if (checkStreamErrors(stream)){
            return("Error: invalid argument");   
        }
        else if (checkResistance(resistance)){
            return("Error: negative resistance");
        }
        else{
            stream >> ws;
            if (stream.eof()) 
                return("Error: too few arguments");
            
            stream >> nodeId1;
            
            if (checkStreamErrors(stream) || (stream.peek()=='.')){
                return("Error: invalid argument");
            }
            else if (validInt(stream)){
                return("Error: invalid argument");
            }
            else if (checkNodeRange(nodeId1, ss)){
                    string nodeOutOfBounds;
                    getline(ss,nodeOutOfBounds);
                    return(nodeOutOfBounds);
            }
            else{
                stream >> ws;
                if (stream.eof()) 
                    return("Error: too few arguments");
                
                stream >> nodeId2;

                if (checkStreamErrors(stream) || (stream.peek()=='.')){
                    return("Error: invalid argument");
                }
                else if (validInt(stream)){
                    return("Error: invalid argument");
                }
                else if (checkNodeRange(nodeId2, ss)){
                    string nodeOutOfBounds;
                    getline(ss,nodeOutOfBounds);
                    return(nodeOutOfBounds);
                }
                else if(nodeId1 == nodeId2){
                    string sameNodeError;

                    ss << "Error: both terminals of resistor connect to node " << nodeId1;
                    getline(ss, sameNodeError);
                    return(sameNodeError);
                }
                stream >> ws;
                if (!stream.eof())
                    return("Error: too many arguments"); 
                
                else{                
                    string success;
    
                    ss << "Inserted: resistor " << name << " " << fixed << setprecision(2) << resistance
                         << " Ohms " << nodeId1 << " -> " << nodeId2;
                    getline (ss, success);
    
                    return(success);
                }
            }
        }
    }   
}

string modifyR(stringstream & stream){    
    
    
    string name;
    double resistance;
    stringstream ss;

    stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    
    stream >> name;
            
    if(checkStreamErrors(stream))       
        return("Error: invalid argument");
    
    else if (checkNameErrors(name))
        return("Error: resistor name cannot be the keyword \"all\"");
    
    else{
        stream >> ws;
        if (stream.eof()) 
            return("Error: too few arguments");
        
        stream >> resistance;
        
        if (checkStreamErrors(stream))
            return("Error: invalid argument");   
        
        else if (checkResistance(resistance))
            return("Error: negative resistance");       

        else{
            stream >> ws;
            if (!stream.eof())
                return("Error: too many arguments");
            
            else{     
                string success;

                ss << "Modified: resistor " << name << " to " << fixed << setprecision(2) << resistance << " Ohms ";
                getline (ss, success);

                return(success);
            }
        }
    }   
}

string printR(stringstream & stream){    
    
    
    string name;
    stringstream ss;

    stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    
    stream >> name;
    
    if(checkStreamErrors(stream))
        return("Error: invalid argument");
    
    else if (checkNameErrors(name))
        return("Print: all resistors");
    
    else{
        stream >> ws;
        if (!stream.eof())
            return("Error: too many arguments");
        
        else{                   
            string success;

            ss << "Print: resistor " << name;
            getline (ss, success);

            return(success);
        }
    }   
}

string printNode(stringstream & stream){    
    
    
    int nodeId;
    string all;
    stringstream ss;

    stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    
    stream >> nodeId;
    
    if(stream.fail() || ((stream.peek() != ' ') && !stream.eof())){ 
        stream.clear();
        stream >> all;        
        if(all == "all"){
            stream >> ws;
            if (!stream.eof())
                return("Error: too many arguments");
           
            else return("Print: all nodes");
        }
        else return("Error: invalid argument");
    }
    else{       
        if (validInt(stream))
                return("Error: invalid argument");
        
        stream >> ws;
        if (checkNodeRange(nodeId, ss)){
                string nodeOutOfBounds;
                getline(ss,nodeOutOfBounds);
                return(nodeOutOfBounds);
        }
        else if (!stream.eof())
            return("Error: too many arguments");
        
        else{   
            string success;

            ss << "Print: node " << nodeId;
            getline (ss, success);

            return(success);
        }
    }   
}

string deleteR(stringstream & stream){    
    
   
    string name;
    stringstream ss;

    stream >> ws;
    if (stream.eof()) 
        return("Error: too few arguments");
    
    stream >> name;
    
    if(checkStreamErrors(stream))
        return("Error: invalid argument");   

    else if (checkNameErrors(name)){
        stream >> ws;
        if (!stream.eof())
            return("Error: too many arguments");
        
        else return("Deleted: all resistors");
    }
    else{
        stream >> ws;
        if (!stream.eof())
            return("Error: too many arguments");
        
        else{           
            string success;
            
            ss << "Deleted: resistor " << name;
            getline (ss, success);

            return(success);
        }
    }   
}

bool checkStreamErrors(stringstream & stream){
    if(stream.fail() || ((stream.peek() != ' ') && !stream.eof())){
        stream.clear();
        stream.ignore(1000, '\n');
        return true;
    }
    else return false;
}
bool checkNameErrors(string name){
    if (name == "all")       
        return true;
    
    else return false;
}
bool checkNodeRange(int node, stringstream & ss){
    if ((node < 0) || (node > MAX_NODE_NUMBER)) {
        ss << "Error: node " << node << " is out of permitted range " << 0 << "-" << MAX_NODE_NUMBER;
        return true;
    }
    else return false;
}
bool checkResistance(double resistance){
    if (resistance < 0) 
        return true;
    
    else return false;
}
bool validInt(stringstream & stream){
    if (stream.peek() == '.' || stream.peek() == 'e')       
        return true;
    
    else return false;
}

