#ifndef LINK_US_RES_H
#define LINK_US_RES_H
#include "User.h"
#include "Resource.h"

class Link_us_res
{
private:
    User  *userPtr;
    Resource *resourcePtr;
public:
    Link_us_res(User *u=nullptr, Resource *r=nullptr);
    //hacer el destructor para que sea esta clase la que se encargue de borrarse de los arrays de user y resources.
    void connectCourseUser();
    bool checkUserKind(string id);
};


#endif // LINK_US_RES_H
