#ifndef FDP_H
#define FDP_H
#include <string>
#include "Resource.h"
#include "Link_us_res.h"

class Degree;

class FDP: public Resource
{

private:
    Link_us_res *tutor;
    Link_us_res *co_tutor;
    Link_us_res *student;

public:

    FDP(string id="undefined", Link_us_res *stu=nullptr, string s="unknown",  Link_us_res *t =nullptr, Link_us_res *c_t=nullptr);
    FDP(const FDP &other);
    FDP& operator= (const FDP &other);
    Link_us_res& gettutor()const;
    void settutor(Link_us_res* t);
    Link_us_res& getco_tutor()const;
    void setco_tutor(Link_us_res* c_t);
    Link_us_res& getstudent()const;
    void setstudent(Link_us_res* stu);


    //---------------
    void addteacher(Link_us_res *newteacher);
    void addstudent(Link_us_res *newstudent);
};

#endif // FDP_H
