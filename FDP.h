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
    Link_prof_res *teachers[2];
    Link_stu_res *student; //Link_us_res *student;

    //---------------
    void addteacher(Link_prof_res *newteacher);
    void addstudent(Link_stu_res *newstudent);
    void removestudent(Link_stu_res *student);
    void removeprofessor(Link_prof_res *link);

public:
    friend class Link_stu_res;
    friend class Link_prof_res;


    FDP(string id="undefined", Student *stu=nullptr, string s="unknown",  Professor *tu =nullptr,Professor *co_tu=nullptr);
    FDP(const FDP &other);
    FDP& operator= (const FDP &other);
    Link_prof_res* gettutor()const; //Link_us_res& gettutor()const;
    void settutor(Professor* t); //void settutor(Link_us_res* t);
    Link_prof_res* getco_tutor()const; //Link_us_res& getco_tutor()const;
    void setco_tutor(Professor* c_t); //void setco_tutor(Link_us_res* c_t);
    Link_stu_res* getstudent()const; //Link_us_res& getstudent()const;
    void setstudent(Student* stu); //void setstudent(Link_us_res* stu);

};

#endif // FDP_H
