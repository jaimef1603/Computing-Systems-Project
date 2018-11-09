#include "Resource.h"
#include <iostream>

Resource::Resource(string id, string s):identification(id), status(s){}

Resource::Resource(const Resource& r)
    :identification(r.identification), status(r.status)
{
    if (r.identification.c_str()==nullptr || r.status.c_str()==nullptr){
        std::cerr<<"Resource cpyconstructor: (Warning) some atribute of original object is invalid.\n";
    }
}


Resource::~Resource(){

}


Resource& Resource::operator= (const Resource& r){
    if (r.identification.c_str()==nullptr || r.status.c_str()==nullptr){
        std::cerr<<"Resource::operator= : (Error) Some atribute of original object is invalid. Object not copied.\n";
    }else{
        identification=r.identification;
        status=r.status;
    }
    return *this;
}

string Resource::getIdentification(){
     return identification;
}



string Resource::getstatus(){
    //comprobar que el estado sea correcto
     return status;
}


void Resource::setIdentification(string id){

    //Comprobar que id cumple las condiciones para ser asignado
     identification=id;
}


void Resource::setstatus(string s){
     status=s;
}


