#include "Professor.h"
#include <string>
#include "Utilities.h"
#include "VirtualCampus.h"

Professor::Professor()
    : User(), identifier("0"), courselist(), fdplist(), seminarlist()
{
    mycampus=nullptr;
}



Professor::Professor(string ident, VirtualCampus *vc)
    :User(), courselist(), fdplist(), seminarlist()
{
    identifier=ident;
    mycampus=vc;
}



Professor::Professor(const Professor& other)
    :User()
{
    identifier=other.identifier;
    mycampus=other.mycampus;
    this->courselist=other.courselist;
    this->fdplist=other.fdplist;
    this->seminarlist=other.seminarlist;
}



string Professor::getidentifier()
{
    return identifier;
}



void Professor::setidentifier(string ident)
{
    identifier=ident;
}



void Professor::removeResource(Link_prof_res *link)
{
    int flag = courselist.remove(link) + seminarlist.remove(link)+fdplist.remove(link);
    if(flag==0){
        cerr<<"Student::removeResource(Link_stu_res*); Nothing to remove.\n";
    }
}



void Professor::showdetails()
{
    cout<<"ID: "<<identifier<<endl;
    cout<<"Courses: "<<courselist.getsize()<<endl;
    cout<<"Seminars: "<<seminarlist.getsize()<<endl;
    cout<<"FDPs: "<<fdplist.getsize()<<endl;
}



void Professor::edit()
{
    string ident;
    bool valid = false;
    cout<<"You can only edit the ID.\n ";
    cout<<"Enter the new ID (7 chars) or \"cancel\" to exit: ";
    do{
        cin>>ident;
        if (ident=="cancel"){
            return;
        }
        if (ident.length()==7 && checkletters(ident)){
            valid = true;
        }else{
            system("clear");
            cout<<"Enter the new ID (7 chars) or \"cancel\" to exit: ";
        }
    }while (!valid);

    if (valid){
        this->identifier=ident;
    }

}



void Professor::options()
{

    char selection;
    do {
        system ("clear");
        cout<<"1: Seminars \n2: Courses \n3:FDPs \n4: Back\n";
        cin>>selection;
        switch (selection) {
        case '1': manageSeminars(); break;
        case '2':
            manageCourses(); break;
        case '3':

        case '4': return;

        default: cout<<"Select a valid number (1-4)\n\tPress any key to retry."<<endl;

            getchar();
            break;

        }
    }while(true);
}






void Professor::manageSeminars()
{
    char selection;
    do {
        cout<<"SEMINARS:\n 1:Add 2:Delete 3:Back\n"<<endl;
        cin>>selection;

        switch (selection) {
        case '1':
        {           char r;
            string identification;
            int valid=-1;
            do {
                system("clear");
                mycampus->showAllSeminars();
                cin>>identification;
                if (identification == "cancel"){
                    break;
                }
                valid=mycampus->findSeminar(identification);

            }while(valid==-1);
            if (valid!=-1){
                do {
                    system("clear");
                    cout<<"Select Role: 1: Speaker\n2: Coordinator";
                    cin>>r;
                    switch (r) {
                    case '1':
                        enroll(mycampus->getSeminars()[unsigned(valid)], role::speaker);
                        return;
                    case '2':
                        enroll(mycampus->getSeminars()[unsigned(valid)], role::coordinator);
                        return;
                    case '3': return;
                    default: break;
                    }

                }while(true);

            }
        }
            break;
        case '2':{
            int index;
            do{
                system("clear");
                cout<<"Seminars of "<<this->getidentifier()<<" :"<<endl;
                for(int i=0; i<seminarlist.getsize(); i++){
                    cout<<seminarlist[i]->getResource().getIdentification()<<endl;
                }
                cout<<"Enter the id of the seminar you want to remove?\n";
                cin>>index;
            }while ((index<0 && index !=-1) || index>=seminarlist.getsize());

            delete seminarlist[index];
        }
            break;
        case '3': return;
        }
    }while (true);
}



void Professor::manageCourses()
{
    char selection;
    do {
        cout<<"SEMINARS:\n 1:Add 2:Delete 3:Back\n"<<endl;
        cin>>selection;

        switch (selection) {
        case '1':
            selectCourseAndAdd();
            break;
        case '2':{
            int index;
            do{
                system("clear");
                cout<<"Seminars of "<<this->getidentifier()<<" :"<<endl;
                for(int i=0; i<seminarlist.getsize(); i++){
                    cout<<seminarlist[i]->getResource().getIdentification()<<endl;
                }
                cout<<"Enter the id of the seminar you want to remove?\n";
                cin>>index;
            }while ((index<0 && index !=-1) || index>=seminarlist.getsize());

            delete seminarlist[index];
        }
            break;
        case '3': return;
        }
    }while (true);
}



void Professor::selectCourseAndAdd(){
    int index;
    char r;
    Degree *current;
    string identification;
    int valid=-1;

    do {
        system("clear");
        mycampus->showAllDeg();
        cout<<"Select the Degree to choose a Course: 1- "<<mycampus->getDegrees().size()<<")"<<endl;
        cin>>index;
    }while((index<1 && index!=-1)|| index> int(mycampus->getDegrees().size()));

    if (index!=-1){
        current= mycampus->getDegrees()[unsigned(index)-1];

        do {
            system("clear");
            current->showcourses();

            cin>>ws>>identification;
            if (identification == "cancel"){
                break;
            }
            valid=current->findCourse(identification);

        }while(valid==-1);
        if (valid!=-1){
            do {
                system("clear");
                cout<<"Select Role: 1: Named Chair\n2: Associated";
                cin>>r;
                switch (r) {
                case '1':
                    enroll(current->getCourses()[unsigned(valid)], role::named_chair);
                    return;
                case '2':
                    enroll(current->getCourses()[unsigned(valid)], role::associated);
                    return;
                case '3': return;
                default: break;
                }

            }while(true);

        }
    }

}




void Professor::addResource(ArrayList<Link_prof_res*> &list, Link_prof_res* link){
    list.pushFront(link);
}



void Professor:: enroll(Course* c, role r)
{
    Link_prof_res *newlink= new Link_prof_res (this, c, r);
    newlink->connectProftoCourse();
    newlink->connectResource();
}


void Professor:: enroll(Seminar* s, role r)
{
    Link_prof_res *newlink= new Link_prof_res (this, s, r);
    newlink->connectProftoSeminar();
    newlink->connectResource();
}



void Professor:: enroll(FDP* project, role r)
{
    Link_prof_res *newlink= new Link_prof_res (this, project, r);
    newlink->connectProftoFDP();
    newlink->connectResource();
}



void Professor::addCourse(Link_prof_res *link){
    this->courselist.pushBack(link);
}



void Professor::addSeminar(Link_prof_res *link)
{
    this->seminarlist.pushBack(link);
}



void Professor::addFDP(Link_prof_res *link)
{
    this->fdplist.pushBack(link);
}

int Professor::menu(){
return 0;
}


//void Professor::exitResource(){
//    bool valid;
//    for(int i=0; i<courselist.getsize(); i++){
//        cout<<"Courses of"<<this->getidentifier()<<": "<<endl;
//        cout<<"ID: "<<courselist[i]->getResource().getIdentification()<<endl;
//    }

//    for(int i=0; i<seminarlist.getsize(); i++){
//        cout<<"Seminars of"<<this->getidentifier()<<": "<<endl;
//        cout<<"ID: "<<seminarlist[i]->getResource().getIdentification()<<endl;
//    }


//    for(int i=0; i<fdplist.getsize(); i++){
//        cout<<"FDPs of"<<this->getidentifier()<<": "<<endl;
//        cout<<"ID: "<<fdplist[i]->getResource().getIdentification()<<endl;
//    }

//    do {
//        cout<<"Enter the ID of the resource you want to exit:"<<endl;


//    }

//}
