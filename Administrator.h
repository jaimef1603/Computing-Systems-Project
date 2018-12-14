#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include "Professor.h"

class Administrator: public Professor{


private:

    void admin_submenu();
    void professor_submenu();
public:

    Administrator( VirtualCampus *vc=nullptr, string n="undefined",string id= "unknown");

    void menu();
    ofstream& loadtofile(ofstream & file);
    friend ofstream & operator<< (ofstream& ofs, Administrator& _admin);

};

#endif // ADMINISTRATOR_H
