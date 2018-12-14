#ifndef STUDENT_H
#define STUDENT_H
#include "ArrayList.h"
#include "User.h"
#include "Link_stu_res.h"
#include "Resource.h"
#include "Degree.h"
class Degree;
class Course;
class Seminar;
class FDP;

class Student: public User
{
private:

    unsigned SIN;
    Degree *mydegree;
    ArrayList <Link_stu_res*> mycourses;
    ArrayList <Link_stu_res*> myseminars;
    Link_stu_res *myfdp;

    //Add functions

    void addCourse(Link_stu_res *link);
    void addSeminar(Link_stu_res *link);
    void addFDP(Link_stu_res *link);

    //Remove function

     void removeResource(Link_stu_res *link);

public:
    static unsigned count;
    friend class Link_stu_res;
    Student();
    Student(Degree *d, string n="undefined");
    Student (const Student &);
    ~Student();
    Student& operator=(const Student&);
    friend ostream& operator<<(ostream& os, const Student& stu);

    void setCount(unsigned c);
    unsigned getCount();
    unsigned getSIN();
    void setSIN(unsigned s);
    string getidentifier();

    //Course functions

    void my_courses();
    void course_droppin_func();
    void course_enrolling_func();
    void course_view();
    void Drop(Course *c);
    void enroll(Course *cour);
    void showCourses();

    //Seminar functions

    void my_seminars();
    void seminar_droppin_func();
    void seminar_enrolling_func();
    void seminar_view();
    void Drop(Seminar *s);
    void enroll(Seminar *setminar);
    void showSeminars();

    //FDP functions

    void my_fdps();
    void fdp_droppin_func();
    void fdp_enrolling_func();
    void fdp_view();
    void Dropfdp();
    void enroll(FDP *project);
    void showFDP();


    void showDetails();
    void options();
    void menu();

    Menu<Student>::menu_option_member gimme_the_id();


    //FILE HANDLING
    friend bool Degree::writeSeminarsLinks();
    friend bool Degree::loadCoursesLinks();
    friend ofstream & operator<< (ofstream& ofs, Student& _student);
    friend ifstream & operator>> (ifstream& ifs, Student& _student);


};

#endif // STUDENT_H
