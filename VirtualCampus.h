#ifndef VIRTUALCAMPUS_H
#define VIRTUALCAMPUS_H
#include "Administrator.h"
#include "Professor.h"
#include "Seminar.h"
#include "Degree.h"

class VirtualCampus
{

private:
    Administrator *admins;
    Professor *proflist;
    Degree *degreelist;
    Seminar *seminalist;
    void *user;
public:
    VirtualCampus();
    ~VirtualCampus();
    void start();
    int run();
    void end();
};

#endif // VIRTUALCAMPUS_H
