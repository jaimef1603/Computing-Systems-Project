#ifndef DEGREE_H
#define DEGREE_H
#include <string>
#include "Student.h"
#include "Course.h"
#include "FDP.h"

using namespace std;

class VirtualCampus;
class Degree
{
private:
    string name;
    VirtualCampus *vc;
    int student_number;
    Student *stulist;
    int course_number;
    Course *courselist;

    void addCourse();
    void deleteCourse(int index);
    void editcourse();
    void addStudent();


public:
    Degree();
    Degree(string n, VirtualCampus *mycampus);
    ~Degree();
    string getname();
    VirtualCampus& getVc();
    Student* searchStudentbyid(string id);
    int getstudent_number();
    void setname(string n);
    void edit();
    void manageCourses();
    void manageStudents();
    void showdetails();
    void showstudents();
    void showcourses();
    Course* getCourses();
    Student* getStudents();
    int findStudent(string identification);
    int findCourse(string identification);
    void options();
};

#endif // DEGREE_H
