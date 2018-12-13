#ifndef DEGREE_H
#define DEGREE_H
#include <string>
#include "Student.h"
#include "Course.h"
#include "FDP.h"
#include <vector>
#include "Menu.h"

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
    Degree(VirtualCampus *mycampus, string n = "undefined", const char *id="unknown");
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
    vector <Student*>& getStudents();
    void showstudents();

    //Course functions

    void manageCourses();
    int findCourse(string identification);
    vector<Course*> getCourses();
    void showcourses();


    void showdetails();
    void edit();
    void options();
    static Menu<Degree>::menu_option_member gimme_the_name();



    friend ofstream & operator<< (ofstream& ofs, Degree& _degree);
    friend ifstream & operator>> (ifstream& ifs, Degree& _degree);

};

#endif // DEGREE_H
