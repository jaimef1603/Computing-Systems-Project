#ifndef DEGREE_H
#define DEGREE_H
#include <string>
#include "Student.h"
#include "Course.h"
#include "FDP.h"
#include <vector>

using namespace std;

class VirtualCampus;
class Degree
{
private:
    string name;
    char id[4];
    VirtualCampus *vc;
    vector <Student*> stulist;
    vector <Course*> courselist;

    void addCourse();
    void deleteCourse(unsigned index);
    void editcourse();
    void addStudent();
    void deleteStudent(unsigned index);
    void editstudent();


public:
    Degree();
    Degree(string n, const char *id,  VirtualCampus *mycampus);
    ~Degree();
    string getname();
    void setname(string n);
    const char* getid();
    VirtualCampus& getVc();

    //Student functions

    Student* searchStudentbyid(string id);
    int getstudent_number();
    void manageStudents();
    int findStudent(string identification);
    vector <Student*> getStudents();
    void showstudents();

    //Course functions

    void manageCourses();
    int findCourse(string identification);
    vector<Course*> getCourses();
    void showcourses();


    void showdetails();
    void edit();
    void options();
};

#endif // DEGREE_H
