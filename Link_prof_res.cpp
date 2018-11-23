#include "Link_prof_res.h"
#include <iostream>
#include "Resource.h"
#include "Professor.h"


Link_prof_res::Link_prof_res(Professor *p, Resource *r, role ro)
    :Link_us_res (r)
{
    if (p!=nullptr){
        profPtr=p;
        papel=ro;
    }else{
        std::cerr<<"Link_prof_res::Link_prof_res(Professor*, Resource*); invalid student.\n";
        this->~Link_prof_res();
    }
}

Link_prof_res::Link_prof_res(const Link_prof_res& other)
    :Link_us_res (other)
{
    this->profPtr=other.profPtr;
    this->papel=other.papel;
}



Link_prof_res::~Link_prof_res()
{
    this->destroy();
}



Link_prof_res& Link_prof_res::operator= (const Link_prof_res &other){
    this->Link_us_res::operator=(other);
    this->papel=other.papel;
    return *this;
}



bool Link_prof_res::operator== (const Link_prof_res &other)
{
    return (resourcePtr==other.resourcePtr && profPtr==other.profPtr )? true:false;
}

role Link_prof_res::getRole()
{
    return papel;
}


int Link_prof_res::checkHealth(){
    if(profPtr==nullptr && resourcePtr==nullptr){
            return -2;
    }else if(profPtr!=nullptr && resourcePtr!=nullptr){
        return 0;
    }else{
        return -1;
    }
}



void Link_prof_res::destroy(){

    resourcePtr->removeprofessor(this);
    profPtr->removeResource(this);

}
