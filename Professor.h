#ifndef PROFESSOR_H
#define PROFESSOR_H
#include <string>
#include "ArrayList.h"
#include "Course.h"
#include "Seminar.h"
#include "FDP.h"
using namespace std;

class Professor
{
protected:
    string identifier;
    ArrayList<Course*> coursePtrlist;
    ArrayList<FDP*> fdpPtrlist;
    ArrayList<Seminar*> seminarPtrlist;
public:
    Professor();
    Professor(string ident);
    void setidentifier(string ident);
    string getidentifier();
};

#endif // PROFESSOR_H
