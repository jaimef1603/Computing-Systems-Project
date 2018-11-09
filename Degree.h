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

public:
    Degree();
    Degree(string n);
    ~Degree();
    string getname();
    Student* searchStudentbyid(string id);
    int getstudent_number();
    void setname(string n);
    void addCourse();
    void editcourse();
    void addStudent();
    void addFDP();
    void showstudents();
    void showcourses();
};

#endif // DEGREE_H
