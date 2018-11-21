#include <cstring>
#include <iostream>
#include "Link_us_res.h"



using namespace std;



Link_us_res::Link_us_res(Resource *r)
{
    if (r!=nullptr){
        resourcePtr=r;
    }else {
        std::cerr<<"Link_us_res::Link_us_res(Resource*); invalid resource.\n";
        this->~Link_us_res();
    }
}



Link_us_res::Link_us_res(const Link_us_res& other)
{
    this->resourcePtr=other.resourcePtr;
}



Link_us_res::~Link_us_res()
{

}



Link_us_res& Link_us_res::operator=(const Link_us_res& other)
{
    this->resourcePtr=other.resourcePtr;
    return *this;
}



Resource& Link_us_res::getResource(){
    return *resourcePtr;
}


void Link_us_res::connectCourseUser(){
  // userPtr->addCourse(this);
}



//bool Link_us_res::checkUserKind(){
//    char *identifier= nullptr;
//    int tamano = static_cast<int> (userPtr->getidentifier().length());
//    identifier =new char [tamano+1];

//    strcpy(identifier, this->userPtr->getidentifier().c_str());

//    for(int i=0;i<tamano;i++){
//        if(identifier[i]<'0' || identifier[i]>'9'){
//            return false;
//        }
//    }
//    return true;

//    //check if id belongs to a student (has only numbers)
//    //returns true if student
//    //returns false if professor or admin

//}
