#ifndef LINK_PROF_RES_H
#define LINK_PROF_RES_H
#include "Link_us_res.h"
#include <string>
class Professor;

enum class role{
   speaker,
   coordinator,
   intern,
   associated,
   tutor,
   cotutor,
    undefined
};
class Link_prof_res : public Link_us_res
{
    Professor *profPtr;
    role papel;

public:
    Link_prof_res(Professor *p=nullptr, Resource *r=nullptr, role ro=role::undefined);
    Link_prof_res(const Link_prof_res& other);
    Link_prof_res& operator= (const Link_prof_res& other);
    ~Link_prof_res();
    bool operator== (const Link_prof_res &other);
    int checkHealth();
    void setRole(role r);
    role getRole();
    std::string getRoleName();
    void destroy();
};

#endif // LINK_PROF_RES_H
