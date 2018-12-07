#include "Administrator.h"
#include "VirtualCampus.h"
#include <sstream>

Administrator::Administrator(string n,string id, VirtualCampus *vc):Professor(n, id, vc){

}



int Administrator::menu()
{
    char selection;
        system("clear");
        cout<<"ADMINISTRATOR: "<<this->identifier<<endl;;
        cout<<"  1: Manage Degrees\n  2: Manage Teachers\n  3:Manage Seminars\n  4:Manage FDP's\n  5:Exit\n";
        cin>>ws>>selection;
        switch (selection) {
        case '1': mycampus->manageDegrees(); return 1;
        case '2': mycampus->manageTeachers(); return 1;
        case '3': mycampus->manageSeminarsVc();
        case '4': mycampus->manageFDPs();
        case '5': return 0;

        default:
            cout<<"Enter a valid number(1-5).\n\tPress any key to retry.\n"<<endl;
            getchar();
            return 1;
        }

}



//int Administrator::menu(){
//    fflush(stdout);
//    system("clear");1

//    int selection;
//    cout<<"1: User\n2: Degree\n3: Resource\n4: Exit\n";
//    cin>>selection;
//    switch (selection) {
//    case 1:
//        manageUser();
//        break;
//    case 2:
//        manageDegree();
//        break;
//    case 3:
//        manageResource();
//        break;
//    case 4:
//        return 0;
//    }
//    return 1;
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
