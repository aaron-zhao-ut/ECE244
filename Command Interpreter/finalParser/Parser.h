#ifndef PARSER_H
#define PARSER_H

using namespace std;

string insertR(stringstream & );
string modifyR(stringstream & );
string printR(stringstream & );
string printNode(stringstream &);
string deleteR(stringstream &);

bool checkStreamErrors(stringstream &);  
bool checkNameErrors(string);            
bool checkNodeRange(int, stringstream &);
bool checkResistance(double);            
bool validInt(stringstream &);          


#endif /* PARSER_H */

