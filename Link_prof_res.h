#ifndef LINK_PROF_RES_H
#define LINK_PROF_RES_H
#include "Link_us_res.h"
#include "Professor.h"

class Link_prof_res : public Link_us_res
{
    Professor *profPtr;
    enum class role{
       speaker,
       coordinator
    } papel;

public:
    Link_prof_res(Professor *p=nullptr, Resource *r=nullptr);
    Link_prof_res(const Link_prof_res& other);
    Link_prof_res& operator= (const Link_prof_res& other);
    int checkHealth();
    void setRole(role r);
    role getRole();
    string getRoleName();

};

#endif // LINK_PROF_RES_H
