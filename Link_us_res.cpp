#include <cstring>

#include "Link_us_res.h"
using namespace std;

Link_us_res::Link_us_res(User *u, Resource *r){
    userPtr=u;
    resourcePtr=r;
}
Date Link_us_res::getdate(){
    return dlink;
}
void Link_us_res::setdate(Date d3){
    d3=dlink;
}

void Link_us_res::connectCourseUser(){
   userPtr->addCourse(this);
}

bool Link_us_res::checkUserKind(){
    char *identifier=this->userPtr->getidentifier().c_str();

    if(identifier<48 || identifier>57){
        return false;
    }else{
        return true;
    }
    //check if id belongs to a student (has only numbers)
    //returns true if student
    //returns false if professor or admin

}
