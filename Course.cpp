#include "Course.h"



Course::Course(string id, Degree *d, int c, string s, Link_prof_res **t)
    :Resource(id, s)
{
    degree=d;
    credits=c;
    if (t!=nullptr){ //we should check as well if the links link to teacher.
        for (int i=0; i<2; i++){
            teachers[i]=t[i];
        }
    }else{
        for (int i=0; i<2; i++){
            teachers[i]=nullptr;
        }
    }
}



Course::Course(const Course &c)
    :Resource(c.identification, c.status)
{
    if (c.identification.c_str()==nullptr || c.status.c_str()==nullptr || c.degree==nullptr){
        std::cerr<<"Course cpyconstructor: (Warning) some atribute of original object is invalid.\n";
    }
    degree=c.degree;
    credits=c.credits;
    studentlist=c.studentlist;
    for (int i=0; i<2; i++){
        if (c.teachers[i]!=nullptr){
            teachers[i]=c.teachers[i];
        }else{
            teachers[i]=nullptr;
        }
    }
}



Course& Course::operator= (const Course &c)
{
    if (c.identification.c_str()==nullptr || c.status.c_str()==nullptr || c.degree==nullptr){
        std::cerr<<"Course:operator=(const Course&); (Warning) Some atribute of original object is invalid, *this will not be modified.\n";
    }else{
        identification=c.identification;
        status=c.status;
        degree=c.degree;
        credits=c.credits;
        studentlist=c.studentlist;
        for (int i=0; i<2; i++){
            if (c.teachers[i]!=nullptr){
                teachers[i]=c.teachers[i];
            }else{
                teachers[i]=nullptr;
            }
        }
    }

    return *this;

}



int Course::getcredits()
{
    return credits;
}



void Course::setcredits(int c)
{
    credits=c;
}



void Course::addteacher(Link_prof_res *newteacher)
{

}



void Course::addstudent(Link_stu_res *newstudent)
{

}

//void Course::addUser(User *newUser){
//link_us_res *newLink= new(newUser, this)
//newLink->checkUserKind(newUser.getidentifier()); (returns if teacher or student)
//if teacher add to teachers[2] if there aren't two teachers yet;
//if student add to studentlist
//and add to courselist of student.
//studentlist.pushFront(newLink);
//newLink->connectCourseUser();

//}
