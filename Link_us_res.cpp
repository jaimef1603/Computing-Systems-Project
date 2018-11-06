#include <cstring>

#include "Link_us_res.h"
using namespace std;

Link_us_res::Link_us_res(User *u, Resource *r){
    userPtr=u;
    resourcePtr=r;
}

void Link_us_res::connectCourseUser(){
   userPtr->addCourse(this);
}

bool Link_us_res::checkUserKind(){
    char *identifier= nullptr;
    int tamaño = static_cast<int> (userPtr->getidentifier().length());
    identifier =new char [tamaño+1];

    strcpy(identifier, this->userPtr->getidentifier().c_str());

    for(int i=0;i<tamaño;i++){
        if(identifier[i]<'0' || identifier[i]>'9'){
            return false;
        }
    }
    return true;

    //check if id belongs to a student (has only numbers)
    //returns true if student
    //returns false if professor or admin

}
