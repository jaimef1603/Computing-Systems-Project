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


public:
    Professor();
    Professor(VirtualCampus *vc = nullptr, string n = string(), string ident = string());
    Professor(const Professor &other);
    void setidentifier(string ident);
    string getidentifier();

    //Resource functions

    void addResource(ArrayList<Link_prof_res*> &list, Link_prof_res *link);
    void removeResource(Link_prof_res *link);

    //Course functions
    //  Used by administrator
    void manageCourses();
    void selectCourseAndAdd();

    //  Used by professor
    void my_courses();
    void course_droppin_func();
    void course_enrolling_func();
    void course_view();

    //  Common
    void addCourse(Link_prof_res *link);
    void enroll(Course* c, role r);
    void Drop(Course* );
    void showCourses();

    //Seminar functions
    //  Used by administrator
    void manageSeminars();


    //  Used by professor
    void my_seminars();
    void seminar_droppin_func();
    void seminar_enrolling_func();
    void seminar_view();

    // Common
    void addSeminar(Link_prof_res *link);
    void enroll(Seminar* s, role r);
    void Drop(Seminar* );
    void showSeminars();



    //FDP functions
    //  Used by administrator
    void manageFDP();
    void deleteFDP();
    void admin_addFDP();
    void addFDP(Link_prof_res *link);

    //  Used by professor
    void my_fdps();
    void fdp_droppin_func();
    void fdp_enrolling_func();
    void fdp_view();

    //  Common
    void enroll(FDP* project, role r);
    void Drop(FDP*);
    void showFDP();




    void showDetails();
    void edit();
    void options();
    virtual void menu(); //must be virtual to be overriden by admin's menu.


    //FILE HANDLING


    friend ofstream & operator<< (ofstream& ofs, Professor& _professor);
    friend ifstream & operator>> (ifstream& ifs, Professor& _professor);


};

#endif // PROFESSOR_H
