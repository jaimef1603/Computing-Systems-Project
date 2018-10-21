#ifndef SEMINAR_H
#define SEMINAR_H
#include <string>
#include "Date.h"
#include "Resource.h"
using namespace std;

class Seminar
{
private:
    //coordinator
    //speaker
    Date* d;
    int seats;
    //student
public:
    Seminar();
    void setseats(int s);
    int getseats();
    void setdate(int d2);
    Date getdate();

};

#endif // SEMINAR_H
