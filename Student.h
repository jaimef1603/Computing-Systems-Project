﻿#ifndef STUDENT_H
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

    void addCourse(Link_stu_res *link);
    void removeResource(Link_stu_res *link);
    void addSeminar(Link_stu_res *link);
    void addFDP(Link_stu_res *link);
public:
    static unsigned count;
    friend class Link_stu_res;
    Student();
    Student(string n, Degree *d);
    Student (const Student &);
    ~Student();
    Student& operator=(const Student&);
    void setCount(unsigned c);
    unsigned getCount();
    unsigned getSIN();
    void setSIN(unsigned s);
    string getidentifier();
    void showDetails();
    void Drop(Course *c);
    void Drop(Seminar *s);
    void Dropfdp();
    void enroll(Course *cour);
    void enroll(Seminar *setminar);
    void enroll(FDP *project);
    void options();
    int menu();

    Menu<Student>::menu_option_member gimme_the_id();
    friend ostream& operator<<(ostream& os, const Student& stu);
};

#endif // STUDENT_H
