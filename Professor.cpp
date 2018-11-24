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

int Professor::menu(){

}
