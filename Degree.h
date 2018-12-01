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
    const char* getid();
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
    vector<Course*> getCourses();
    vector <Student*> getStudents();
    int findStudent(string identification);
    int findCourse(string identification);
    void options();
};

#endif // DEGREE_H
