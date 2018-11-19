﻿#ifndef SEMINAR_H
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
    Link_prof_res *coordinator;  //Link_us_res *coordinator;
    Link_prof_res *speaker; //Link_us_res *speaker;
    Date eventDate;
    int maxseats;
    int freeseats;
    Link_stu_res *students; //Link_us_res *students;
public:
    Seminar(string id="undefined", string s="unknown", int seatsValue=0,User *spe =nullptr, User *coord=nullptr);
    Seminar(string id, string s, int seatsValue, Date when, User *spe, User *coord);
    void setmaxseats(int s);
    int getmaxseats()const;
    void setdate(Date when);
    Date getdate()const;
    void setspeaker(User *spe);
    Link_prof_res& getspeaker()const; //Link_us_res& getspeaker()const;
    void setcoordinator(User *coord);
    Link_prof_res& getcoordinator()const; //Link_us_res& getcoordinator()const;

    //----------
    void addteacher(Link_prof_res *newteacher);//void addteacher(Link_us_res *newteacher);
    void addstudent(Link_stu_res *newstudent);//void addstudent(Link_us_res *newstudent);
};

#endif // SEMINAR_H
