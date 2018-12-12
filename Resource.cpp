#include "Resource.h"
#include <iostream>
#include "Utilities.h"
#include <sstream>
#include <limits>

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



Resource::~Resource()
{

}



Resource& Resource::operator= (const Resource& r)
{
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



void Resource::editName()    //Function to edit the resource name
{
    std::string buffer;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do {
       system("clear");
       if (!cin.good()){
           cin.clear();
           std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
       }
       std::cout<<"Enter the new name or \'q\' to cancel: ";

    }while(!getline(cin, buffer, '\n') || !checkletters(buffer));

    if (buffer!="q"){
        name=buffer;
    }

}



Menu<Resource>::menu_option_member Resource::gimmethename()
{
    return &Resource::name;
}



Menu<Resource>::menu_option_member Resource::gimmetheid()
{
    return &Resource::identification;

}



//---------- FILE HANDLING-----------------


 ofstream & operator<< (ofstream& ofs, Resource* _resource)
{
     unsigned long length = _resource->name.size();
     const char *name = _resource->name.c_str();
     const char *id = _resource->identification.c_str();
     ofs.write(reinterpret_cast<char*>(&(length)), sizeof (unsigned long));
     ofs.write(name,  static_cast<long>(length * sizeof (char)));
     ofs.write(id,  8 * sizeof (char));
     return ofs;
}



ifstream & operator>> (ifstream& ifs, Resource* _resource)
{
    unsigned long length;
    ifs.read(reinterpret_cast<char*>(&(length)), sizeof (unsigned long));
    char * name=new char[length];
    ifs.read(name,  static_cast<long>(length * sizeof (char)));
    _resource->name=name;
    char * id=new char [8];
    ifs.read(id, 8 * sizeof (char));
    _resource->identification=id;
    delete [] id;
    delete [] name;
    return ifs;
}
