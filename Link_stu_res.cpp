﻿#include "Link_stu_res.h"
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



Link_stu_res& Link_stu_res::operator= (const Link_stu_res &other)
{
    this->Link_us_res::operator=(other);
    //falta por copiar las notas
    return *this;
}



bool Link_stu_res::operator== (const Link_stu_res &other)
{
    return (resourcePtr==other.resourcePtr && stuPtr==other.stuPtr )? true:false;
}



int Link_stu_res::checkHealth()
{
    if(stuPtr==nullptr && resourcePtr==nullptr){
        return -2;
    }else if(stuPtr!=nullptr && resourcePtr!=nullptr){
        return 0;
    }else{
        return -1;
    }
}



Student& Link_stu_res::getStudent()
{
    return *stuPtr;
}



void Link_stu_res::setfinalMark(float value, Date when)
{
    final=Mark(value, when);
}



void Link_stu_res::setfinalMark(Mark value){
    final=Mark(value);
}



void Link_stu_res::setpartialMark(float value, Date when, int position)
{
    for(int i=0;i<position;i++){
        partial[i]=Mark(value, when);
    }
}



void Link_stu_res::setpartialMark(Mark value, int position)
{
    for(int i=0;i<position;i++){
        partial[i]=Mark(value);
    }
}



void Link_stu_res::setpartialMark(Mark value[])
{
    for(int i=0;i<4;i++){
        partial[i]=value[i];
    }
}


Mark& Link_stu_res::getfinalMark()
{
    return final;
}


Mark* Link_stu_res::getpartiaMark()
{
    return partial;
}



void Link_stu_res::connectStutoCourse()
{
    stuPtr->addCourse(this);
}



void Link_stu_res::connectStutoSeminar()
{
    stuPtr->addSeminar(this);
}



void Link_stu_res::connectStutoFDP()
{
    stuPtr->addFDP(this);
}



void Link_stu_res::connectResource()
{
    resourcePtr->addstudent(this);
}



void Link_stu_res::destroy()
{
    resourcePtr->removestudent(this);
    stuPtr->removeResource(this);
}



void Link_stu_res::showDetails()
{
    resourcePtr->showDetails();

    if (this->resourcePtr->getname().find_first_of("SEM")!=0 && this->resourcePtr->getname().find_first_of("FDP")!=0){

        cout<<"GRADES:"<<endl
           <<"\tPartial:"<<endl;
        for (unsigned i=0; i<4; i++){
            cout<<"\t "<<i<<": ";
            if (partial[i].getvalue()==-1){
                cout<<"Not Graded"<<endl;
            }else{
                cout<<partial[i].getvalue()<<" Date: "<<partial[i].getdate_graded();
            }
        }
        cout<<"Final: ";
        if(final.getvalue()==-1){
            cout<<"Not graded"<<endl;
        }else{
            cout<<final.getvalue()<<" Date: "<<final.getdate_graded()<<endl;

        }
    }

}

