#ifndef USER_H
#define USER_H
#include <string>

class Link_us_res;

class User
{
private:

public:
    virtual ~User();
    virtual void menu()=0
            ;
    virtual std::string getidentifier()=0;
    //virtual void addCourse(Link_us_res *link);
    //virtual void addSeminar(Link_us_res *link);
    //virtual void addFDP(Link_us_res *link);
};

#endif // USER_H
