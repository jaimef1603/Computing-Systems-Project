#include "FDP.h"
#include <iostream>

FDP::FDP(string id, Link_stu_res *stu, string s, Link_prof_res *t, Link_prof_res *c_t)
    :Resource(id, s)
{
    tutor = t;
    co_tutor = c_t;
    student = stu;
}



FDP::FDP(const FDP &other)
    :Resource(other.identification, other.status)
{
    tutor = other.tutor;
    co_tutor = other.co_tutor;
    student = other.student;

}



FDP& FDP::operator= (const FDP &other)
{
    this->Resource::operator=(other);
    tutor=other.tutor;
    co_tutor=other.co_tutor;
    student=other.student;

    return *this;
}



Link_prof_res& FDP::gettutor()const
{
    return *tutor;
}



void FDP::settutor(Link_prof_res* t)
{
    if (t!=nullptr && !t->checkHealth()){
        tutor=t;
    }else{
        std::cerr<<"FDP::settutor(Link_prof_res*); incomplete or null link passed, tutor will not be modified.\n";
    }
}



Link_prof_res& FDP::getco_tutor()const
{
    return *co_tutor;
}



void FDP::setco_tutor(Link_prof_res* c_t)
{
    if (c_t!=nullptr && !c_t->checkHealth()){
        tutor=c_t;
    }else{
        std::cerr<<"FDP::setco_tutor(Link_prof_res*); incomplete or null link passed, co_tutor will not be modified.\n";
    }
}



Link_stu_res& FDP::getstudent()const
{
    return *student;
}



void FDP::setstudent(Link_stu_res* stu)
{
    if (stu!=nullptr && !stu->checkHealth()){
        tutor=stu;
    }else{
        std::cerr<<"FDP::setstudent(Link_stu_res*); incomplete or null link passed, student will not be modified.\n";
    }
}



void FDP::addteacher(Link_prof_res *newteacher)
{

}



void FDP::addstudent(Link_stu_res *newstudent)
{

}






