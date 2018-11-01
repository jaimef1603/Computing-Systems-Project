#ifndef DEGREE_H
#define DEGREE_H
#include <string>
#include "Student.h"
#include "Course.h"
#include "FDP.h"

using namespace std;


class Degree
{
private:
    string name;
    int student_number;
    Student *stulist;
    int course_number;
    Course *courselist;
    int fdp_number;
    FDP *projectlist;

public:
    Degree();
    Degree(string n);
    string getname();
    void setname(string n);
    void addCourse();
    void addStudent();
    void addFDP();
};

#endif // DEGREE_H
