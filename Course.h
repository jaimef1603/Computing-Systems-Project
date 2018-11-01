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
    ArrayList <Link_us_res*> studentlist;
    Degree *degree;
    Link_us_res   *teachers[2];
    ArrayList <Mark> class_marks;

public:
    Course(string id="undefined", string s="unknown", int c=6, Degree *d=nullptr, Link_us_res **t=nullptr);
    Course(const Course&);
    Course& operator= (const Course&);
    int getcredits();
    void setcredits(int c);

    //polymorphism starts
    void addUser(User *newUser);
};

#endif
