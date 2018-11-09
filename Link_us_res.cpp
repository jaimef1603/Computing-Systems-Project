#include <cstring>

#include "Link_us_res.h"
using namespace std;

Link_us_res::Link_us_res(User *u, Resource *r){
    userPtr=u;
    resourcePtr=r;
}

void Link_us_res::connectCourseUser(){
  // userPtr->addCourse(this);
}

int Link_us_res::checkHealth(){
    if(userPtr==nullptr && resourcePtr==nullptr){
            return -2;
    }else if(userPtr!=nullptr && resourcePtr!=nullptr){
        return 0;
    }else{
        return -1;
    }
}

bool Link_us_res::checkUserKind(){
    char *identifier= nullptr;
    int tamano = static_cast<int> (userPtr->getidentifier().length());
    identifier =new char [tamano+1];

    strcpy(identifier, this->userPtr->getidentifier().c_str());

    for(int i=0;i<tamano;i++){
        if(identifier[i]<'0' || identifier[i]>'9'){
            return false;
        }
    }
    return true;

    //check if id belongs to a student (has only numbers)
    //returns true if student
    //returns false if professor or admin

}
