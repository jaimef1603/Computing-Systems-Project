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



string Link_prof_res::getRoleName()
{
    switch (papel) {

    case role::speaker: return "Speaker";
    case role::coordinator: return "Coordinator";
    case role::named_chair: return "Named Chair";
    case role::associated: return "Associated";
    case role::tutor: return "Tutor";
    case role::cotutor: return "Cotutor";
    case role::undefined: return "Undefined";
    }

    return "Unknown";
}



int Link_prof_res::checkHealth()
{
    if(profPtr==nullptr && resourcePtr==nullptr){
            return -2;
    }else if(profPtr!=nullptr && resourcePtr!=nullptr){
        return 0;
    }else{
        return -1;
    }
}



Professor* Link_prof_res::getteacher()
{
    return profPtr;
}



void Link_prof_res::connectProftoCourse()
{
    profPtr->addCourse(this);
}



void Link_prof_res::connectProftoSeminar()
{
    profPtr->addSeminar(this);
}



void Link_prof_res::connectProftoFDP()
{
    profPtr->addFDP(this);
}



void Link_prof_res::connectResource()
{
    resourcePtr->addteacher(this);
}



void Link_prof_res::destroy()
{
    resourcePtr->removeprofessor(this);
    profPtr->removeResource(this);

}
