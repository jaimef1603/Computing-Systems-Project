#include "Administrator.h"
#include "VirtualCampus.h"
#include <sstream>

Administrator::Administrator(VirtualCampus *vc, string n,string id):Professor(vc, n, id){

}


void Administrator::admin_submenu ()
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
    options.emplace_back(2, &Administrator::professor_submenu, "Acces the professor menu", this);


        Menu<Administrator> menu(options, "---WELCOME TO YOUR MAIN MENU---\n You currently have administration rights");// &Administrator::showDetails, this);

        menu.run();


}

//}

//void Administrator::manageResource()
//{
//    system("clear");
//    int selection;
//    cout<<"1: Create\n2: Edit\n";
//    cin>>selection;
//    switch(selection){
//    case 1:
//        createResource();
//        break;
//    case 2:
//        editResource();
//        break;
//    }
//}


//void Administrator::createResource()
//{
//    system("clear");
//    int selection;
//    cout<<"1 create course\n2 create seminar\n3 create fdp\n";
//    cin>>selection;
//    switch (selection) {
//    case 1: mycampus->addCourse();
//        break;
//    case 2: mycampus->addseminar();
//        break;
//    case 3: mycampus->addFDP();
//        break;
//    default: break;
//    }
//}



//void Administrator::editResource()
//{
//    system("clear");
//    int selection;
//    cout<<"1 edit course\n2 edit seminar\n3 edit fdp\n";
//    cin>>selection;
//    switch (selection) {
//    case 1: mycampus->editcourse();
//        break;
//    case 2: mycampus->editseminar();
//        break;
//    case 3: mycampus->editFDP();
//        break;
//    default: break;
//    }
//}
