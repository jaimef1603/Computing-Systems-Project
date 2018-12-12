#ifndef LINK_STU_RES_H
#define LINK_STU_RES_H
#include "Link_us_res.h"
#include "Mark.h"

class Student;

class Link_stu_res : public Link_us_res
{
    Student *stuPtr;
    Mark partial[4];
    Mark final;
public:
    Link_stu_res(Student *s=nullptr, Resource *r=nullptr);
    Link_stu_res(const Link_stu_res& other);
    ~Link_stu_res();
    Link_stu_res& operator= (const Link_stu_res &other);
    bool operator== (const Link_stu_res &other);
    int checkHealth();
    Student& getStudent();
    void setfinalMark(float value, Date when);
    void setfinalMark(Mark value);
    void setpartialMark(float value, Date when, int position);
    void setpartialMark(Mark value, int position);
    void setpartialMark(Mark value[4]);
    Mark& getfinalMark();
    Mark* getpartiaMark();


    //Connect functions

    void connectStutoCourse();
    void connectStutoSeminar();
    void connectStutoFDP();
    void connectResource();
    void destroy();

    //Student functions
    void showDetails();

    //professor functions
    void grade();
};

#endif // LINK_STU_RES_H
