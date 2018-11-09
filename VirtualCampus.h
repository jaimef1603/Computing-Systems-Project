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
    VirtualCampus();
    ~VirtualCampus();
    void editDegree();
    void addDegree();
    void editFDP();
    void addFDP();
    void editseminar();
    void addseminar();
    void editcourse();
    void addCourse();
    void start();
    int run();
    void end();
};

#endif // VIRTUALCAMPUS_H
