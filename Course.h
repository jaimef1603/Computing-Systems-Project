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
    ArrayList <Link_stu_res*> studentlist;
    Degree *degree;
    Link_prof_res   *teachers[2];

    //--------------------------------------

    void addteacher(Link_prof_res *newteacher);
    void addstudent(Link_stu_res *newstudent);
    void removestudent(Link_stu_res *student);
    void removeprofessor(Link_prof_res *professor);

public:
    friend class Link_stu_res;
    friend class Link_prof_res;
    Course(Degree *d=nullptr, string n="unknown",string id="undefined",  int c=6, Link_prof_res **t=nullptr);
    Course(const Course&);
    ~Course();
    Course& operator= (const Course&);
    int getcredits();
    void setcredits(int c);
    vector<Link_stu_res*>& getStudents();
    void edit();
    void editID();
    void options();
    void showDetails();
    void grade();


    //FOR FILES

    friend ofstream & operator<< (ofstream& ofs, Course& _course);
    friend ifstream& operator>>(ifstream& ifs, Course& _course);


};

#endif
