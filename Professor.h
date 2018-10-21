#ifndef PROFESSOR_H
#define PROFESSOR_H
#include <string>
using namespace std;

class Professor
{
protected:
    string ID;
    //courses
    //FDP
    //seminars
public:
    Professor();
    void setID(string ident);
    string getID();
};

#endif // PROFESSOR_H
