#ifndef FDP_H
#define FDP_H
#include <string>
#include "Resource.h"
#include "Link_prof_res.h"
#include "Link_stu_res.h"

class Degree;
class VirtualCampus;
class FDP: public Resource
{

private:
    VirtualCampus* mycampus;
    Link_prof_res *teachers[2];
    Link_stu_res *student;

    //---------------
    void addteacher(Link_prof_res *newteacher);
    void addstudent(Link_stu_res *newstudent);
    void removestudent(Link_stu_res *student);
    void removeprofessor(Link_prof_res *link);

    void options_settttutor();
    void options_ssseeeetCo_tuttor();
    void options_setstudent();
    void options_removeStudent();


public:
    friend class Link_stu_res;
    friend class Link_prof_res;


    FDP(string n="unknown", string id="undefined", VirtualCampus *vc=nullptr,  Student *stu=nullptr,  Professor *tu =nullptr,Professor *co_tu=nullptr);
    FDP(const FDP &other);
    FDP& operator= (const FDP &other);
    Link_prof_res* gettutor()const;
    void settutor(Professor* t);
    Link_prof_res* getco_tutor()const;
    void setco_tutor(Professor* c_t);
    Link_stu_res* getstudent()const;
    void setstudent(Student* stu);
    void setvc(VirtualCampus * vc){ mycampus = vc;}
    VirtualCampus* getvc(){return mycampus;}
    void edit();
    void editID();
    void options();
    void showDetails();

};

#endif // FDP_H
