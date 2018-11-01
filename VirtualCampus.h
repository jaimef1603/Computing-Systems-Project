#ifndef VIRTUALCAMPUS_H
#define VIRTUALCAMPUS_H
#include "Administrator.h"
#include "Professor.h"
#include "Student.h"
#include "Course.h"
#include "Seminar.h"
#include "FDP.h"


class VirtualCampus
{

private:
    Administrator *admins;
    Student *stulist;
    Professor *proflist;
    Course *courselist;
    Seminar *seminalist;
    FDP *projectlist;
    void *user;
public:
    VirtualCampus();
    ~VirtualCampus();
    void start();
    int run();
    void end();
};

#endif // VIRTUALCAMPUS_H
