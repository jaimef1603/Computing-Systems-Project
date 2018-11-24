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

    int SIN;
    const Degree *mydegree;
    ArrayList <Link_stu_res*> mycourses;//ArrayList <Link_us_res*> mycourses; //triple!!! investigar si todo funciona correcto.
    ArrayList <Link_stu_res*> myseminars;//ArrayList <Link_us_res*> myseminars;
    Link_stu_res *myfdp; //Link_us_res *myfdp;

    void addCourse(Link_stu_res *link);
    void removeResource(Link_stu_res *link);
    void addSeminar(Link_stu_res *link);
    void addFDP(Link_stu_res *link);
public:
    static int count;
    friend class Link_stu_res;
    Student();
    Student(Degree &d);
    Student (const Student &);
    ~Student();
    Student& operator=(const Student&);
    void setCount(int c);
    int getCount();
    int getSIN();
    void setSIN(int s);
    string getidentifier();
    void showDetails();
    void Drop(Course *c);
    void Drop(Seminar *c);
    void Dropfdp();
    void enroll(Course *cour);
    void enroll(Seminar *setminar);
    void enroll(FDP *project);
    void options();
    int menu();

    friend ostream& operator<<(ostream& os, const Student& stu);
};

#endif // STUDENT_H
