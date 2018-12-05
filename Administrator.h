#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include "Professor.h"
//#include "VirtualCampus.h"

class Administrator: public Professor{


private:

    void createResource();
    void editResource();
public:
    Administrator(string n="undefined",string id= "xxxxxx", VirtualCampus *vc=nullptr);

    //Polymorphism starts
    int menu();

};

#endif // ADMINISTRATOR_H
