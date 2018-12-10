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



Resource* Link_us_res::getResource(){
    return resourcePtr;
}

