#include "Administrator.h"
#include "VirtualCampus.h"
#include <sstream>

Administrator::Administrator(VirtualCampus *vc, string n,string id):Professor(vc, n, id){

}


void Administrator::admin_submenu()
{
    vector<Menu<VirtualCampus>::Menu_option> admin_options;
    admin_options.reserve(4);
    admin_options.emplace_back(1, &VirtualCampus::manageDegrees, "Manage Degrees", mycampus);
    admin_options.emplace_back(2, &VirtualCampus::manageTeachers, "Manage Teachers", mycampus);
    admin_options.emplace_back(3, &VirtualCampus::manageSeminars, "Manage Seminars", mycampus);
    admin_options.emplace_back(4, &VirtualCampus::manageFDPs, "Manage FDPs", mycampus);
    Menu<VirtualCampus> admin_menu (admin_options, "VIRTUAL CAMPUS ADMINISTRATOR MENU");

    admin_menu.run();
}



void Administrator::professor_submenu()
{
    Professor::menu();
}



void Administrator::menu()
{

    vector<Menu<Administrator>::Menu_option> options;
    options.reserve(2);
    options.emplace_back(1, &Administrator::admin_submenu, "Access the administrator menu", this);
    options.emplace_back(2, &Administrator::professor_submenu, "Access the professor menu", this);


        Menu<Administrator> menu(options, "---WELCOME TO YOUR MAIN MENU---\n You currently have administration rights");

        menu.run();

}



ofstream& Administrator::loadtofile(ofstream & file)
{
   file<<*this;
   return file;
}



ofstream & operator<< (ofstream& ofs, Administrator& _admin)
{
    bool isadmin = true;
    ofs.write(reinterpret_cast<char*>(&isadmin), sizeof (bool));
    ofs << &_admin;
    const char *id = _admin.identifier.c_str();
    ofs.write(id,  8 * sizeof (char));
    unsigned long seminar_number = _admin.seminarlist.size();
    unsigned long course_number = _admin.courselist.size();
    unsigned long fdp_number = _admin.fdplist.size();
    ofs.write(reinterpret_cast<char*>(&seminar_number), sizeof(unsigned long));
    ofs.write(reinterpret_cast<char*>(&course_number), sizeof(unsigned long));
    ofs.write(reinterpret_cast<char*>(&fdp_number), sizeof(unsigned long));
    return ofs;
}

