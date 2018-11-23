#include "Administrator.h"
#include "VirtualCampus.h"


Administrator::Administrator(string id, VirtualCampus *vc):Professor(id)
{
    mycampus=vc;
}

Administrator::Administrator(string ident, const Administrator &admin):Professor(ident){

}



void Administrator::manageUser()
{
    system("clear");
    cout<<"Not implemented yet\n";
    getchar();
}



void Administrator::manageResource()
{
    system("clear");
    int selection;
    cout<<"1: Create\n2: Edit\n";
    cin>>selection;
    switch(selection){
    case 1:
        createResource();
        break;
    case 2:
        editResource();
        break;
    }
}

void Administrator::manageDegree()
{

    system("clear");
    int selection, deg;
    mycampus->showAllDeg();
    cout<<"1: Create 2: Edit 3: Delete 4:Details 5: Select 6:Back\n";
    cin>>selection;
    switch(selection){
    case 1:
        mycampus->addDegree();
        break;
    case 2:
        do {
            system("clear");
            cout<<"DEGREES:\n";
            mycampus->showAllDeg();
            cout<<"What degree do you want to edit?\n";
            cin>>ws>>deg;
            if (deg<1 || deg >mycampus->degree_number){
                cout<<"Select a valid number. (0-"<<mycampus->degree_number<<")\n";
            }
        }while(deg<1 || deg >mycampus->degree_number);
        system("clear");
        mycampus->degreelist[deg].edit();
        break;
    case 3:
        do {
            system("clear");
            cout<<"DEGREES:\n";
            mycampus->showAllDeg();
            cout<<"What degree do you want to delete?\n";
            cin>>ws>>deg;
            if (deg<1 || deg >mycampus->degree_number){
                cout<<"Select a valid number. (0-"<<mycampus->degree_number<<")\n";
            }
        }while(deg<1 || deg >mycampus->degree_number);
        system("clear");
        mycampus->deleteDegree(deg);
        break;
    case 4:
        do {
            system("clear");
            mycampus->showAllDeg();
            cout<<"What degree do you want to show details of?\n";
            cin>>ws>>deg;
            if (deg<1 || deg >mycampus->degree_number){
                cout<<"Select a valid number. (0-"<<mycampus->degree_number<<")\n";
            }
        }while(deg<1 || deg >mycampus->degree_number);
        system("clear");
        mycampus->degreelist[deg].showdetails();

        break;
    case 5:
        do {
            system("clear");
            mycampus->showAllDeg();
            cout<<"What degree do you want to show details of?\n";
            cin>>ws>>deg;
            if (deg<1 || deg >mycampus->degree_number){
                cout<<"Select a valid number. (0-"<<mycampus->degree_number<<") or -1 to exit\n";
            }
        }while((deg<1 && deg!=-1)|| deg >mycampus->degree_number);
        system("clear");
        if (deg!=-1){
            mycampus->degreelist[deg].options();
        }
        break;
    case 6: break;
    }

}

//int Administrator::menu(){
//    fflush(stdout);
//    system("clear");
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


int Administrator::menu(){

}


void Administrator::createResource()
{
    system("clear");
    int selection;
    cout<<"1 create course\n2 create seminar\n3 create fdp\n";
    cin>>selection;
    switch (selection) {
    case 1: mycampus->addCourse();
        break;
    case 2: mycampus->addseminar();
        break;
    case 3: mycampus->addFDP();
        break;
    default: break;
    }
}



void Administrator::editResource()
{
    system("clear");
    int selection;
    cout<<"1 edit course\n2 edit seminar\n3 edit fdp\n";
    cin>>selection;
    switch (selection) {
    case 1: mycampus->editcourse();
        break;
    case 2: mycampus->editseminar();
        break;
    case 3: mycampus->editFDP();
        break;
    default: break;
    }
}
