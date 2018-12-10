#ifndef SEMINAR_H
#define SEMINAR_H
#include <string>
#include "Date.h"
#include "Resource.h"
#include "Link_prof_res.h"
#include "Link_stu_res.h"
#include "ArrayList.h"

using namespace std;

class VirtualCampus;

class Seminar: public Resource
{
private:
    VirtualCampus * mycampus;
    Link_prof_res *teachers[2];
    Date eventDate;
    unsigned maxseats;
    ArrayList <Link_stu_res *> students;

    //----------
    void addteacher(Link_prof_res *newteacher);
    void addstudent(Link_stu_res *newstudent);
    void removestudent(Link_stu_res *link);
    void removeprofessor(Link_prof_res *link);

    void editID();
    void editDate();
    void editMaxseats();
    void options_coordinator();
    void options_speaker();
    void options_addstudent();
    void options_removestudent();

public:
    friend class Link_stu_res;
    friend class Link_prof_res;
    Seminar(string n="unknown", string id="undefined", VirtualCampus *vc = nullptr, unsigned seatsValue=0, Professor *coord=nullptr,  Date when=Date(1, 1, 1), Professor *spe=nullptr);
  //  Seminar(string n, string id, unsigned seatsValue, Professor *coord, Date when=Date(1, 1, 1));
    void setmaxseats(unsigned s);
    unsigned getmaxseats()const;
    void setdate(Date when);
    Date getdate()const;
    void setspeaker(Professor *spe);
    Link_prof_res* getspeaker()const;
    void setcoordinator(Professor *coord);
    Link_prof_res* getcoordinator()const;
    void setvc(VirtualCampus * vc){ mycampus = vc;}
    VirtualCampus* getvc(){return mycampus;}

    void showDetails();
    void options();
    void edit();



};

#endif // SEMINAR_H
