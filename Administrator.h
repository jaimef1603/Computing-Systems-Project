﻿#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include "Professor.h"
//#include "VirtualCampus.h"

class VirtualCampus;
class Administrator: public Professor{


private:
    VirtualCampus *mycampus;

    void manageUser();
    void manageTeacher();
    void createResource();
    void editResource();
    void manageDegree();
public:
    Administrator(string id= "xxxxxx", VirtualCampus *vc=nullptr);

    //Polymorphism starts
    int menu();

};

#endif // ADMINISTRATOR_H
