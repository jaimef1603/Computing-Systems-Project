#ifndef FDP_H
#define FDP_H
#include <string>
#include "Resource.h"
#include "Link_prof_res.h"
#include "Link_stu_res.h"

class Degree;

class FDP: public Resource
{

private:
    Link_prof_res *tutor; //Link_us_res *tutor;
    Link_prof_res *co_tutor; //Link_us_res *co_tutor;
    Link_stu_res *student; //Link_us_res *student;

public:

    FDP(string id="undefined", Link_stu_res *stu=nullptr, string s="unknown",  Link_prof_res *t =nullptr, Link_prof_res *c_t=nullptr);
    FDP(const FDP &other);
    FDP& operator= (const FDP &other);
    Link_prof_res& gettutor()const; //Link_us_res& gettutor()const;
    void settutor(Link_prof_res* t); //void settutor(Link_us_res* t);
    Link_prof_res& getco_tutor()const; //Link_us_res& getco_tutor()const;
    void setco_tutor(Link_prof_res* c_t); //void setco_tutor(Link_us_res* c_t);
    Link_stu_res& getstudent()const; //Link_us_res& getstudent()const;
    void setstudent(Link_stu_res* stu); //void setstudent(Link_us_res* stu);


    //---------------
    void addteacher(Link_prof_res *newteacher); //void addteacher(Link_us_res *newteacher);
    void addstudent(Link_stu_res *newstudent); //void addstudent(Link_us_res *newstudent);
    void removestudent(Link_stu_res *student);
};

#endif // FDP_H
