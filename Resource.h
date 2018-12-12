#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include "Link_prof_res.h"
#include "Link_stu_res.h"
#include "Menu.h"
#include <fstream>

using namespace std;

class User;
class Link_us_res;
class Resource
{
protected:
    string identification;
    string name;

    //Virtual functions

    virtual void addteacher(Link_prof_res *newteacher)=0;
    virtual void addstudent(Link_stu_res *newstudent)=0;
    virtual void removestudent(Link_stu_res *student)=0;
    virtual void removeprofessor(Link_prof_res *profesor)=0;
public:
    friend class Link_stu_res;
    friend class Link_prof_res;
    Resource(string id="undefined", string n="unknown");
    Resource(const Resource&);
    virtual ~Resource();
    virtual Resource& operator= (const Resource& r); //problematico, revisar bien.
    void setIdentification(string id);
    string getIdentification();
    void setname(string n);
    string getname();
    void editName();
    virtual void editID()=0;
    virtual void showDetails()=0;
    static Menu<Resource>::menu_option_member gimmethename();
    static Menu<Resource>::menu_option_member gimmetheid();


    //FILES

    friend ofstream & operator<< (ofstream& ofs, Resource* _resource);
    friend ifstream & operator>> (ifstream& ifs, Resource* _resource);

};



#endif // RESOURCE_H

