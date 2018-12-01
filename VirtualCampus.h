#ifndef VIRTUALCAMPUS_H
#define VIRTUALCAMPUS_H
#include "Administrator.h"
#include "Professor.h"
#include "Seminar.h"
#include "Degree.h"
#include <vector>
class Administrator;
class VirtualCampus
{

private:
    std::vector <Administrator*> admins;
    std::vector <Professor*> proflist;
    std::vector <Degree*> degreelist;
    std::vector <Seminar*> seminalist;
    std::vector <FDP*> projectlist;
    User *currentuser;

public:
    friend class Administrator;
    VirtualCampus();
    ~VirtualCampus();
    void addTeacher();
    void deleteTeacher(unsigned index);
    int findTeacher(string identification);
    int findSeminar(string identification);
    int findDegree(string identification);
    int findFDP(string identification);
    vector <Degree*> getDegrees();
    vector <Seminar*> getSeminars();
    vector <Professor*> getTeachers();
    void addDegree();
    void deleteDegree(unsigned index);
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
