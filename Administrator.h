#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include "Professor.h"
//#include "VirtualCampus.h"

class Administrator: public Professor{


private:

    void admin_submenu();
    void professor_submenu();
public:
    Administrator(string n="undefined",string id= "xxxxxx", VirtualCampus *vc=nullptr);

    //Polymorphism starts
    void menu();


};

#endif // ADMINISTRATOR_H
