#include "Link_stu_res.h"

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
Link_stu_res& Link_stu_res::operator= (const Link_stu_res &other){
    this->Link_us_res::operator=(other);
    //falta por copiar las notas
    return *this;
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
