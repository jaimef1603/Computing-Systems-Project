#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include "Professor.h"
#include "Seminar.h"
#include "FDP.h"
#include "Degree.h"
class Administrator: public Professor{

private:
    Administrator *AdminPtr;
    Professor *profesorPtr;
    Degree *degreePtr;
    Seminar *seminarPtr;
    FDP *fdpPtr;
    void createUser();
    void createResource();
public:
    Administrator();
    Administrator(string ident, const Administrator &admin);
    //Polymorphism starts
    void menu();
};

#endif // ADMINISTRATOR_H
