﻿#include "Link_prof_res.h"

Link_prof_res::Link_prof_res(Professor *p, Resource *r)
    :Link_us_res (r)
{
    if (p!=nullptr){
        profPtr=p;
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
Link_prof_res& Link_prof_res::operator= (const Link_prof_res &other){
    this->Link_us_res::operator=(other);
    this->papel=other.papel;
    return *this;
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