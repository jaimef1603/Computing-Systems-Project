#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include "Professor.h"
//#include "VirtualCampus.h"

class Administrator: public Professor{


private:

    void admin_submenu();
    void professor_submenu();
public:
    Administrator( VirtualCampus *vc=nullptr, string n="undefined",string id= "unknown");

    //Polymorphism starts
    void menu();


};

#endif // ADMINISTRATOR_H
