#include "Link_us_res.h"

Link_us_res::Link_us_res(User *u, Resource *r){
    userPtr=u;
    resourcePtr=r;
}

void Link_us_res::connectCourseUser(){
   userPtr->addCourse(this);
}

bool Link_us_res::checkUserKind(string id){

    //check if id belongs to a student (has only numbers)
    //returns true if student
    //returns false if professor or admin

}
