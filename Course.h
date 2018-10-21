#ifndef COURSE_H
#define COURSE_H
#include "Resource.h"
#include <string>
using namespace std;

class Course: public Resource{
private:
    int credits;
    //studentlist
    //degree
    //teachers
    //marks
public:
    Course();
    int getcredits();
    void setcredits(int c);
};

#endif // COURSE_H
