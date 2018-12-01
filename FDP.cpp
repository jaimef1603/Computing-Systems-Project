#include "FDP.h"
#include <iostream>
#include "Link_stu_res.h"
#include "Link_prof_res.h"


FDP::FDP(string id, Student *stu, string s, Professor *tu, Professor *co_tu)
    :Resource(id, s)
{
    setstudent(stu);
    settutor(tu);
    setco_tutor(co_tu);

}



FDP::FDP(const FDP &other)
    :Resource(other.identification, other.status)
{
    teachers[0]=other.teachers[0];
    teachers[1]=other.teachers[1];
    student=other.student;

}



FDP& FDP::operator= (const FDP &other)
{
    this->Resource::operator=(other);
    teachers[0]=other.teachers[0];
    teachers[1]=other.teachers[1];
    student=other.student;

    return *this;
}



Link_prof_res* FDP::gettutor()const
{
    for (int i=0; i<2; i++){
        if (teachers[i]->getRole()==role::tutor){
            return teachers[i];
        }

    }
    return nullptr;
}



void FDP::settutor(Professor* t)
{
    Link_prof_res *newlink= new Link_prof_res(t, this, role::tutor);
    if (newlink!=nullptr && !newlink->checkHealth()){
        teachers[0]=newlink;
    }else{
        std::cerr<<"FDP::settutor(Link_prof_res*); incomplete or null link passed, tutor will not be modified.\n";
    }
}



Link_prof_res* FDP::getco_tutor()const
{
    for (int i=0; i<2; i++){
        if (teachers[i]->getRole()==role::cotutor){
            return teachers[i];
        }

    }
    return nullptr;
}



void FDP::setco_tutor(Professor* c_t)
{
    Link_prof_res *newlink= new Link_prof_res(c_t, this, role::cotutor);
    if (newlink!=nullptr && !newlink->checkHealth()){
        teachers[1]=newlink;
    }else{
        std::cerr<<"FDP::setco_tutor(Link_prof_res*); incomplete or null link passed, co_tutor will not be modified.\n";
    }
}



Link_stu_res* FDP::getstudent()const
{
    return student;
}



void FDP::setstudent(Student* stu)
{
    Link_stu_res *newlink = new Link_stu_res(stu, this);
    if (newlink!=nullptr && !newlink->checkHealth()){
        student=newlink;
    }else{
        std::cerr<<"FDP::setstudent(Link_stu_res*); incomplete or null link passed, student will not be modified.\n";
    }
}



void FDP::addteacher(Link_prof_res *newteacher)
{
    if (newteacher->getRole()==role::tutor){
        if(teachers[0]!=nullptr){

            delete teachers[0];
            teachers[0]=newteacher;
            return;

        }else{
            teachers[0]=newteacher;
            return;
        }
    }
    if (newteacher->getRole()==role::cotutor){
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





void FDP::addstudent(Link_stu_res *newstudent)
{
    student=newstudent;
}



void FDP::removestudent(Link_stu_res *link){
    if (student==link && student != nullptr){
        student=nullptr;
    }else{
        cerr<<"FDP::removestudent(Link_stu_res *); Link passed does not correspond to this FDP or there isn´t a student asigned.\n";
    }
}



void FDP::removeprofessor(Link_prof_res* link)
{
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
            cerr<<"FDP::removeprofessor(Link_prof_res*); No teacher removed.\n";
        }
    }
}

