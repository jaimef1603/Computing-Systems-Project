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

class Professor: public User
{
protected:
    string identifier;
    //ArrayList<Link_us_res*> courselist;
    //ArrayList<Link_us_res*> fdplist;
    //ArrayList<Link_us_res*> seminarlist;
    ArrayList<Link_prof_res*> courselist;
    ArrayList<Link_prof_res*> fdplist;
    ArrayList<Link_prof_res*> seminarlist;


    //Polymorphism starts
    //void addCourse(Link_us_res *link);
    //void addSeminar(Link_us_res *link);
    //void addFDP(Link_us_res *link);
public:
    Professor();
    Professor(string ident);
    Professor(const Professor &other);
    void setidentifier(string ident);
    void removeResource(Link_prof_res *link);
    string getidentifier();
    void showdetails();
    void edit();
    void options();
    virtual int menu(); //must be virtual to be overriden by admin's menu.
};

#endif // PROFESSOR_H
