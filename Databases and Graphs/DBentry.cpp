#include "DBentry.h"
DBentry::DBentry(){}
DBentry::~DBentry(){}

DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active){
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}

void DBentry::setName(string _name){
    name = _name;
}
void DBentry::setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
}
void DBentry::setActive(bool _active){
    active = _active;
}

string DBentry::getName() const{
    return(name);
}
unsigned int DBentry::getIPaddress() const{
    return(IPaddress);
}
bool DBentry::getActive() const{
    return(active);
}

ostream& operator<< (ostream& out, const DBentry& rhs){
    string status = "inactive";
    if(rhs.active)
        status = "active";
    
    out << rhs.name << " : " << rhs.IPaddress << " : " << status;
    return(out);
}
