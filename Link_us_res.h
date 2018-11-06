#ifndef LINK_US_RES_H
#define LINK_US_RES_H
#include "User.h"
#include "Resource.h"
#include "Mark.h"
#include "Date.h"
class Link_us_res
{
private:
    User  *userPtr;
    Resource *resourcePtr;
    Mark partial[4];
    Mark final;
public:
    Link_us_res(User *u=nullptr, Resource *r=nullptr);
    void setdate(Date d3);
    Date getdate();
    Link_us_res& operator=(const Link_us_res& otherlink);
    //hacer el destructor para que sea esta clase la que se encargue de borrarse de los arrays de user y resources.
    void connectCourseUser();
    bool checkUserKind();
};


#endif // LINK_US_RES_H
