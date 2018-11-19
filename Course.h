#ifndef COURSE_H
#define COURSE_H
#include "Resource.h"
#include "ArrayList.h"
#include "Link_us_res.h"
#include "Professor.h"
#include "Mark.h"
#include <string>

using namespace std;

class Degree;

class Course: public Resource{
private:
    int credits;
    ArrayList <Link_stu_res*> studentlist; //ArrayList <Link_us_res*> studentlist;
    Degree *degree;
    Link_prof_res   *teachers[2]; //Link_us_res   *teachers[2];

public:
    Course(string id="undefined", Degree *d=nullptr, int c=6, string s="unknown", Link_prof_res **t=nullptr);
    Course(const Course&);
    Course& operator= (const Course&);
    int getcredits();
    void setcredits(int c);
    void addteacher(Link_prof_res *newteacher); //void addteacher(Link_us_res *newteacher);
    void addstudent(Link_stu_res *newstudent); //void addstudent(Link_us_res *newstudent);

};

#endif
