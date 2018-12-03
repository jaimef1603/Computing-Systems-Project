#include "Seminar.h"
#include <iostream>
#include "Link_prof_res.h"

Seminar::Seminar(string n, string id, unsigned seatsValue, Professor *coord, Professor *spe, Date when)
    :Resource(id, n)
{

    maxseats=seatsValue;
    eventDate=when;
    if (coord)
        setcoordinator(coord);
    if (spe)
        setspeaker(spe);
}



Seminar::Seminar(string n, string id, unsigned seatsValue, Professor *coord, Date when)
    :Resource(id, n)
{

    maxseats=seatsValue;
    eventDate=when;
    if (coord)
        setcoordinator(coord);
}



unsigned Seminar::getmaxseats()const
{
    return maxseats;
}



void Seminar::setmaxseats(unsigned s)
{
    maxseats=s;
}



Date Seminar::getdate()const
{
    return eventDate;
}



void Seminar::setdate(Date when)
{
    eventDate=when;
}



void Seminar::setspeaker(Professor *spe)
{

    Link_prof_res *newLink=new Link_prof_res(spe, this, role::speaker);
    if (newLink->checkHealth()==0){
        teachers[0]= newLink;
    }else{
        std::cerr<<"Seminar::setspeaker(User*); failed to create a new link\n";
    }
}



Link_prof_res* Seminar::getspeaker()const
{
    for (int i=0; i<2; i++){
        if (teachers[i]->getRole()==role::speaker){
            return teachers[i];
        }

    }
    return nullptr;
}



void Seminar::setcoordinator(Professor *coord)
{
    Link_prof_res *newLink=new Link_prof_res(coord, this, role::coordinator);
    if (newLink->checkHealth()==0){
        teachers[1]=newLink;
    }else{
        std::cerr<<"Seminar::setcoordinator(User*); failed to create a new link\n";
    }
}



Link_prof_res* Seminar::getcoordinator()const
{

    for (int i=0; i<2; i++){
        if (teachers[i]->getRole()==role::coordinator){
            return teachers[i];
        }

    }
    return nullptr;
}



void Seminar::addteacher(Link_prof_res *newteacher)
{
    if (newteacher->getRole()==role::speaker){
        if(teachers[0]!=nullptr){

            delete teachers[0];
            teachers[0]=newteacher;
            return;

        }else{
            teachers[0]=newteacher;
            return;
        }
    }
    if (newteacher->getRole()==role::coordinator){
        if(teachers[1]!=nullptr){
            delete teachers[1];
            teachers[1]=newteacher;
            return;

        }else{
            teachers[1]=newteacher;
            return;
        }
    }
}




void Seminar::addstudent(Link_stu_res *newstudent)
{
    bool flag = false;
    if (students.getsize()<maxseats){
        students.pushFront(newstudent);
        flag = true;
    }
    if (!flag){
        cerr<<"Seminar::addstudent(Link_us_res*); Student was not added.\n";
    }
}



void Seminar::removestudent(Link_stu_res *link){
    students.remove(link);
}



void Seminar::removeprofessor(Link_prof_res *link){
    int i;
    bool flag = false;
    for (i=0; i<2; i++){
        if (teachers[i]==link){
            flag = true;
            for(;i<2; i++){
                if (i!=1){
                    teachers[i]=teachers[i+1];
                }else{
                    teachers[i]=nullptr;
                }
            }
            break;
        }

        if (!flag){
            cerr<<"Seminar::removeprofessor(Link_prof_res*); No teacher removed.\n";
        }
    }
}




