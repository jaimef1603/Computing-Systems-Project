#include "Administrator.h"
#include "VirtualCampus.h"


Administrator::Administrator(string id, VirtualCampus *vc):Professor(id)
{
    mycampus=vc;
}

Administrator::Administrator(string ident, const Administrator &admin):Professor(ident){

}

void Administrator::createDegree(){

}

void Administrator::menu(){
    int selection;
    cout<<"1 create degree\n2 create course\n3 create seminar\n4 create fdp\n";
    cin>>selection;
    switch (selection) {
    case 1: mycampus->addDegree();
        break;
    case 2: mycampus->addCourse();
        break;
    case 3: mycampus->addseminar();
        break;
    case 4: mycampus->addFDP();
        break;
    default: break;
    }
}
