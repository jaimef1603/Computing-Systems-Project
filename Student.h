#ifndef STUDENT_H
#define STUDENT_H
#include "ArrayList.h"
#include "User.h"
#include "Link_us_res.h"
#include "Resource.h"
class Degree;
class Course;
class Seminar;
class FDP;

class Student: public User
{
private:
    int SIN;
    const Degree *mydegree;
    ArrayList <Link_us_res*> mycourses; //triple!!! investigar si todo funciona correcto.
    ArrayList <Link_us_res*> myseminars;
    Link_us_res *myfdp;
    void addCourse(Link_us_res *link);
    void addSeminar(Link_us_res *link);
    void addFDP(Link_us_res *link);
public:
    Student(int sin=0);
    Student(int sin, Degree &d);
    Student (const Student &);
    Student& operator=(const Student&);
    int getSIN();
    void setSIN(int s);
    string getidentifier();
    void enroll(Resource *res);
    void menu();

};

#endif // STUDENT_H
