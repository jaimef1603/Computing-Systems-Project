#ifndef STUDENT_H
#define STUDENT_H
#include "ArrayList.h"
#include "User.h"
#include "Link_stu_res.h"
#include "Resource.h"

class Degree;
class Course;
class Seminar;
class FDP;

class Student: public User
{
private:

    unsigned SIN;
    const Degree *mydegree;
    ArrayList <Link_stu_res*> mycourses;//triple!!! investigar si todo funciona correcto.
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
    Student(string n, Degree *d);
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

    void Drop(Course *c);
    void enroll(Course *cour);

    //Seminar functions

    void Drop(Seminar *s);
    void enroll(Seminar *setminar);

    //FDP functions

    void Dropfdp();
    void enroll(FDP *project);


    void showDetails();
    void options();
    int menu();

    Menu<Student>::menu_option_member gimme_the_id();

};

#endif // STUDENT_H
