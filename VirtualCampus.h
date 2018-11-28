#ifndef VIRTUALCAMPUS_H
#define VIRTUALCAMPUS_H
#include "Administrator.h"
#include "Professor.h"
#include "Seminar.h"
#include "Degree.h"

class Administrator;
class VirtualCampus
{

private:
    int admin_number;
    Administrator *admins;
    int prof_number;
    Professor *proflist;
    int degree_number;
    Degree *degreelist;
    int seminar_number;
    Seminar *seminalist;
    User *currentuser;
    int fdp_number;
    FDP *projectlist;

public:
    friend class Administrator;
    VirtualCampus();
    ~VirtualCampus();
    void addTeacher();
    void deleteTeacher(int index);
    int findTeacher(string identification);
    int findSeminar(string identification);
    int findDegree(string identification);
    int findFDP(string identification);
    int getDegreeNumber();
    Degree* getDegrees();
    Seminar* getSeminars();
    Professor* getTeachers();
    void addDegree();
    void deleteDegree(int index);
    void showAllDeg();
    void showAllTeach();
    void showAllSeminars();
    void editFDP();
    void addFDP();
    void editseminar();
    void addseminar();
    void start();
    int run();
    void end();
};

#endif // VIRTUALCAMPUS_H
