#include "Resource.h"
#include <iostream>
#include "Utilities.h"
Resource::Resource(string id, string n)
    :identification(id), name(n)

{
}



Resource::Resource(const Resource& r)
    :identification(r.identification), name(r.name)
{
    if (r.identification.empty() || r.name.empty()){
        std::cerr<<"Resource cpyconstructor: (Warning) some atribute of original object is invalid.\n";
    }
}


Resource::~Resource(){

}


Resource& Resource::operator= (const Resource& r){
    if (r.identification.empty() || r.name.empty()){
        std::cerr<<"Resource::operator= : (Error) Some atribute of original object is invalid. Object not copied.\n";
    }else{
        identification=r.identification;
    }
    return *this;
}

string Resource::getIdentification()
{
    return identification;
}



void Resource::setIdentification(string id)
{

        identification=id;

}



void Resource::setname(string n)
{
    name=n;
}



string Resource::getname(){
    return name;
}

