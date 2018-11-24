#include "Administrator.h"
#include "VirtualCampus.h"


Administrator::Administrator(string id, VirtualCampus *vc):Professor(id)
{
    mycampus=vc;
}


void Administrator::manageTeacher()
{
    int selection;
    do{
        system("clear");
        cout<<"1: Create teacher 2: Edit teacher 3: Delete teacher 4: Details 5: Back"<<endl;
        cin>>selection;
        switch (selection) {
        case 1: mycampus->addTeacher(); break;
        case 2: {
            string id;
            int teach=-1;
            system("clear");
            cout<<"Enter the id of the teacher you want to show details.\n";

            do {
                cin>>ws>>id;
                if (id=="cancel"){
                    break;
                }else{
                    teach=mycampus->findTeacher(id);
                }
                if(teach==-1){
                    system("clear");
                    cout<<"Invalid ID\n";
                    cout<<"Enter the id of the teacher you want to show details.\n";
                }
            }while(teach==-1);
            system("clear");
            if (teach!=-1){
                mycampus->proflist[teach].edit();
            }
        }break;
        case 3:
        {
            string id;
            int teach=-1;
            system("clear");
            cout<<"Enter the id of the teacher you want to delete.\n";

            do {
                cin>>ws>>id;
                if (id=="cancel"){
                    break;
                }else{
                    teach=mycampus->findTeacher(id);
                }
                if(teach==-1){
                    system("clear");
                    cout<<"Invalid ID\n";
                    cout<<"Enter the id of the teacher you want to delete.\n";
                }
            }while(teach==-1);
            system("clear");
            if (teach!=-1){
                 mycampus->deleteTeacher(teach);
            }
        }
            break;
        case 4: {
            string id;
            int teach=-1;
            system("clear");
            cout<<"Enter the id of the teacher you want to show details.\n";

            do {
                cin>>ws>>id;
                if (id=="cancel"){
                    break;
                }else{
                    teach=mycampus->findTeacher(id); 
                }
                if(teach==-1){
                    system("clear");
                    cout<<"Invalid ID\n";
                    cout<<"Enter the id of the teacher you want to show details.\n";
                }
            }while(teach==-1);
            system("clear");
            if (teach!=-1){
                mycampus->proflist[teach].showdetails();
            }
        }break;
        case 5: return;
        default:
            cout<<"Enter a valid number(1-5)."<<endl;
        }
    }while(true);
}



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

void Administrator::manageDegree()
{

    char selection;
    int deg;

    do{
        system("clear");
    mycampus->showAllDeg();
    cout<<"1: Create 2: Edit 3: Delete 4:Details 5: Select 6:Back\n";
    cin>>selection;
    switch(selection){
    case '1':
        mycampus->addDegree();
        system("clear");
        break;
    case '2':
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
        mycampus->degreelist[deg-1].edit();
        break;
    case '3':
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
        mycampus->deleteDegree(deg-1);
        break;
    case '4':
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
        mycampus->degreelist[deg-1].showdetails();
        //system("clear");
        break;
    case '5':
        do {
            system("clear");
            mycampus->showAllDeg();
            cout<<"What degree do you want to select?\n";
            cin>>ws>>deg;
            if (deg<1 || deg >mycampus->degree_number){
                cout<<"Select a valid number. (0-"<<mycampus->degree_number<<") or -1 to exit\n";
            }
        }while((deg<1 && deg!=-1)|| deg >mycampus->degree_number);
        system("clear");
        if (deg!=-1){
            mycampus->degreelist[deg-1].options();
        }
        break;
    case '6': return;

    default: cout<<"Enter a valid number(1-5).\n\tPress any key to retry.\n"<<endl;
        getchar();
        break;

    }
    }while(true);

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


int Administrator::menu(){
    char selection;
    do{
        system("clear");
        cout<<"1: Manage Degrees 2: Manage Teachers 3: Exit";
        cin>>ws>>selection;
        switch (selection) {
        case '1': this->manageDegree(); break;
        case '2': this->manageTeacher(); break;
        case '3': return 1;
        default: cout<<"Enter a valid number(1-3).\n\tPress any key to retry.\n"<<endl;
        getchar();
            break;
        }
    }while (true);



}


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
