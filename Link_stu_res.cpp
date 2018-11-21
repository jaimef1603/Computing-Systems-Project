#include "Link_stu_res.h"
#include <iostream>
#include "Resource.h"
#include "Student.h"
Link_stu_res::Link_stu_res(Student *s, Resource *r)
    :Link_us_res (r)
{
    if(s!=nullptr){
        stuPtr=s;
    }else{
        std::cerr<<"Link_stu_res::Link_stu_res(Student*, Resource*); invalid student.\n";
        this->~Link_stu_res();
    }
}



Link_stu_res::Link_stu_res(const Link_stu_res& other)
    :Link_us_res (other)
{
    this->stuPtr=other.stuPtr;
    //falta por iniciar las notas
}

Link_stu_res::~Link_stu_res()
{
    this->destroy();
}

Link_stu_res& Link_stu_res::operator= (const Link_stu_res &other){
    this->Link_us_res::operator=(other);
    //falta por copiar las notas
    return *this;
}



bool Link_stu_res::operator== (const Link_stu_res &other)
{
    return (resourcePtr==other.resourcePtr && stuPtr==other.stuPtr )? true:false;
}



int Link_stu_res::checkHealth(){
    if(stuPtr==nullptr && resourcePtr==nullptr){
            return -2;
    }else if(stuPtr!=nullptr && resourcePtr!=nullptr){
        return 0;
    }else{
        return -1;
    }
}



void Link_stu_res::setfinalMark(float value, Date when){
//    date(when);
//    if(value>=0 && value<=10 || value==-1){
//        final=value;
//    }else{
//        std:cerr<<"Link_stu_res::setfinalMark(float value, Date when); Value not valid, assigning -1";
//        final=-1;
//    }
}



void Link_stu_res::setfinalMark(Mark value){
//    if(value>=0 && value<=10 || value==-1){
//        final=value;
//    }else{
//        std:cerr<<"Link_stu_res::setfinalMark(Mark value); Value not valid, assigning -1";
//        final=-1;
//    }
}



void Link_stu_res::setpartialMark(float value, Date when, int position){
//    Date(when);
//    for(int i=0;i<position;i++){
//        if(value>=0 && value<=10 || value==-1){
//             final=value;
//        }else{
//             std:cerr<<"Link_stu_res::setfinalMark(float value, Date when, int position); Value not valid, assigning -1";
//             final=-1;
//        }
//    }
}



void Link_stu_res::setpartialMark(Mark value, int position){
//    for(int i=0;i<position;i++){
//      if(value>=0 && value<=10 || value==-1){
//        final=value;
//      }else{
//        std:cerr<<"Link_stu_res::setfinalMark(float value, int position); Value not valid, assigning -1";
//        final=-1;
//      }
//    }
}



void Link_stu_res::setpartialMark(Mark value[]){
//    if(value>=0 && value<=10 || value==-1){
//        final=value;
//    }else{
//        std:cerr<<"Link_stu_res::setfinalMark(Mark value[]); Value not valid, assigning -1";
//        final=-1;
//    }
}


Mark& Link_stu_res::getfinalMark(){
    return final;
}


Mark* Link_stu_res::getpartiaMark(){
    return partial;
}



void Link_stu_res::destroy(){
   resourcePtr->removestudent(this);
   stuPtr->removeResource(this);
}
