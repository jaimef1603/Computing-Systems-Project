#include "Resource.h"

Resource::Resource(){   
 }
string Resource::getID(){
     return ID;
}
string Resource::getstatus(){
     return status;
}
void Resource::setID(string i){
     ID=i;
}
void Resource::setstatus(string s){
     status=s;
}

