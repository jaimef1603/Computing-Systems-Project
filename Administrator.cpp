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
    int selection;
    cout<<"1: Create\n2: Edit\n";
    cin>>selection;
    switch(selection){
    case 1:
        mycampus->addDegree();
        break;
    case 2:
        mycampus->editDegree();
        break;
    }
 //case 1: mycampus->addDegree();
}

int Administrator::menu(){
    fflush(stdout);
    system("clear");
    int selection;
    cout<<"1: User\n2: Degree\n3: Resource\n4: Exit\n";
    cin>>selection;
    switch (selection) {
    case 1:
        manageUser();
        break;
    case 2:
        manageDegree();
        break;
    case 3:
        manageResource();
        break;
    case 4:
        return 0;
    }
    return 1;
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
