#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include "Student.h"
#include "Professor.h"
#include "Student.h"
#include "Course.h"
#include "Seminar.h"
#include "FDP.h"
class Administrator: public Professor{


    Administrator *AdminPtr;
    Professor *profesorPtr;
    Student *studentPtr;
    Course *coursePtr;
    Seminar *seminarPtr;
    FDP *fdpPtr;

public:


    Administrator();
    Administrator(string ident, const Administrator &admin);
    void createUser();

};

#endif // ADMINISTRATOR_H
