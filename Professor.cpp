#include "Professor.h"
#include <string>
#include "Utilities.h"

Professor::Professor()
    : User(), identifier("0"), courselist(), fdplist(), seminarlist()
{

}



Professor::Professor(string ident)
    :User(), courselist(), fdplist(), seminarlist()
{
    identifier=ident;
}



Professor::Professor(const Professor& other)
    :User()
{
    identifier=other.identifier;
    this->courselist=other.courselist;
    this->fdplist=other.fdplist;
    this->seminarlist=other.seminarlist;
}



string Professor::getidentifier(){
    return identifier;
}

void Professor::setidentifier(string ident){
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

}



void Professor::options()
{

        int selection;
        cout<<"1: Add to Resource \n2: Remove from Resource \n3: Back\n";
        do {
            cin>>selection;
            if (selection <1 || selection >3){
                system("clear");
                cout<<"1: Add to Resource \n2: Remove from Resource \n3: Back\n";
                cout<<"Select a valid number (1-3) or -1 to exit"<<endl;
            }
        }while((selection <1 && selection !=-1) || selection >3);
        switch (selection) {
        case 1:

        case 2:

        case 3: break;
        }
        return;
}



int Professor::menu(){

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
