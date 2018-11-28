#ifndef PROFESSOR_H
#define PROFESSOR_H
#include <string>
#include "ArrayList.h"
#include "Seminar.h"
#include "FDP.h"
#include "User.h"
#include "Link_us_res.h"

using namespace std;


class Course;
class VirtualCampus;

class Professor: public User
{
protected:
    string identifier;
    VirtualCampus *mycampus;
    ArrayList<Link_prof_res*> courselist;
    ArrayList<Link_prof_res*> fdplist;
    ArrayList<Link_prof_res*> seminarlist;


    //Polymorphism starts
    //void addCourse(Link_us_res *link);
    //void addSeminar(Link_us_res *link);
    //void addFDP(Link_us_res *link);
public:
    Professor();
    Professor(string ident, VirtualCampus *vc);
    Professor(const Professor &other);
    void setidentifier(string ident);
    void addResource(ArrayList<Link_prof_res*> &list, Link_prof_res *link);
    void removeResource(Link_prof_res *link);
    string getidentifier();
    void showdetails();
    void edit();
    void options();
    void addCourse(Link_prof_res *link);
    void addSeminar(Link_prof_res *link);
    void addFDP(Link_prof_res *link);

    void manageCourses();
    void manageSeminars();
    void selectCourseAndAdd();


    void enroll(Course* c, role r);
    void enroll(Seminar* s, role r);
    void enroll(FDP* project, role r);
    virtual int menu(); //must be virtual to be overriden by admin's menu.
};

#endif // PROFESSOR_H
