#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include "Professor.h"
//#include "VirtualCampus.h"

class VirtualCampus;
class Administrator: public Professor{


private:
    VirtualCampus *mycampus;
    void createUser();
    void createResource();
    void createDegree();
public:
    Administrator(string id= "xxxxxx", VirtualCampus *vc=nullptr);
    Administrator(string ident, const Administrator &admin);
    //Polymorphism starts
    void menu();
};

#endif // ADMINISTRATOR_H
