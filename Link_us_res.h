#ifndef LINK_US_RES_H
#define LINK_US_RES_H
#include "User.h"
#include "Resource.h"
#include "Date.h"

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
    virtual int checkHealth()=0;
    void connectCourseUser();
    //bool checkUserKind();
};


#endif // LINK_US_RES_H
