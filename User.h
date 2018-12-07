#ifndef USER_H
#define USER_H
#include <string.h>
#include <iostream>
#include "Menu.h"


using namespace std;


class Link_us_res;

class User
{
protected:
    string name;
public:
    virtual ~User();
    virtual int menu()=0;
    virtual std::string getidentifier()=0;
    void setname(string n);
    string getname();
    static Menu<User>::menu_option_member gimmethename();

    //virtual void addCourse(Link_us_res *link);
    //virtual void addSeminar(Link_us_res *link);
    //virtual void addFDP(Link_us_res *link);
};

#endif // USER_H
