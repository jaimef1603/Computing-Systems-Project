﻿#ifndef VIRTUALCAMPUS_H
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

    //Teacher functions

    void manageTeachers();
    void addTeacher();
    void deleteTeacher(unsigned index);
    int findTeacher(string identification);
    void showAllTeach();
    vector <Professor*>& getTeachers();

    //Degree functions

    void manageDegrees();
    void addDegree();
    void deleteDegree(unsigned index);
    int findDegree(string identification);
    void showAllDeg();
    vector <Degree*>& getDegrees();

    //FDP functions

    void manageFDPs();
    void addFDP();
    void editFDP();
    void deleteFDP();
    void selectFDP();
    int findFDP(string identification);
    void showAllFDP();

    //Seminar functions

    void addseminar();
    void editseminar();
    void selectSeminar();
    void deleteSeminar();
    void showAllSeminars();
    void manageSeminars();
    int findSeminar(string identification);
    vector <Seminar*>& getSeminars();


    void start();
    int run();
    void end();

};

#endif // VIRTUALCAMPUS_H
