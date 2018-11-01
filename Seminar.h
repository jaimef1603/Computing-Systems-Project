#ifndef SEMINAR_H
#define SEMINAR_H
#include <string>
#include "Date.h"
#include "Resource.h"
#include "Link_us_res.h"
using namespace std;

class Seminar: public Resource
{
private:
    Link_us_res coordinator;
    Link_us_res speaker;
    Date d;
    int seats;
    Link_us_res *students;
public:
    Seminar();
    void setseats(int s);
    int getseats();
    void setdate(Date d2);
    Date getdate();
    void addUser(User *newUser);
};

#endif // SEMINAR_H
