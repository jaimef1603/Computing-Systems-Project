#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include "Link_prof_res.h"
#include "Link_stu_res.h"

using namespace std;

class User;
class Link_us_res;
class Resource
{
protected:
    string identification;
    string status;
    //--------
    virtual void addteacher(Link_prof_res *newteacher)=0;
    virtual void addstudent(Link_stu_res *newstudent)=0;
    virtual void removestudent(Link_stu_res *student)=0;
    virtual void removeprofessor(Link_prof_res *profesor)=0;
public:
    friend class Link_stu_res;
    friend class Link_prof_res;
    Resource(string id="undefined", string s ="unknown");
    Resource(const Resource&);
    virtual ~Resource();
    virtual Resource& operator= (const Resource& r); //problematico, revisar bien.
    void setIdentification(string id);
    string getIdentification();
    void setstatus(string s);
    string getstatus();


};

#endif // RESOURCE_H

