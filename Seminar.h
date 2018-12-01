#ifndef SEMINAR_H
#define SEMINAR_H
#include <string>
#include "Date.h"
#include "Resource.h"
#include "Link_prof_res.h"
#include "Link_stu_res.h"

using namespace std;

class Seminar: public Resource
{
private:
    Link_prof_res *teachers[2];
    Date eventDate;
    int maxseats;
    int freeseats;
    Link_stu_res **students;

    //----------
    void addteacher(Link_prof_res *newteacher);
    void addstudent(Link_stu_res *newstudent);
    void removestudent(Link_stu_res *link);
    void removeprofessor(Link_prof_res *link);
public:
    friend class Link_stu_res;
    friend class Link_prof_res;
    Seminar(string id="undefined", string s="unknown", int seatsValue=0,Professor *spe =nullptr, Professor *coord=nullptr);
    Seminar(string id, string s, int seatsValue, Date when, Professor *spe, Professor *coord);
    void setmaxseats(int s);
    int getmaxseats()const;
    void setdate(Date when);
    Date getdate()const;
    void setspeaker(Professor *spe);
    Link_prof_res* getspeaker()const;
    void setcoordinator(Professor *coord);
    Link_prof_res* getcoordinator()const;

    //Seminar(string id, int seatsValue, Date when);

};

#endif // SEMINAR_H
