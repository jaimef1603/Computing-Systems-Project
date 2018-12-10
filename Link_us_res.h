#ifndef LINK_US_RES_H
#define LINK_US_RES_H
#include "User.h"
#include "Date.h"

class Resource;
class Link_us_res
{
protected:
    Resource *resourcePtr;
public:
    Link_us_res(Resource *r=nullptr);
    Link_us_res(const Link_us_res& other);
    virtual ~Link_us_res();
    Link_us_res& operator=(const Link_us_res& other);
    //hacer el destructor para que sea esta clase la que se encargue de borrarse de los arrays de user y resources.
    Resource* getResource();
    virtual int checkHealth()=0;
    virtual void destroy()=0;
    virtual void connectResource()=0;
};


#endif // LINK_US_RES_H
