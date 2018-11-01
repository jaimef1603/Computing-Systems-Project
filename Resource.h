#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
using namespace std;

class User;

class Resource
{
protected:
    string identification;
    string status;
public:
    Resource(string id="undefined", string s ="unknown");
    Resource(const Resource&);
    virtual ~Resource();
    virtual Resource& operator= (const Resource& r); //problematico, revisar bien.
    void setIdentification(string id);
    string getIdentification();
    void setstatus(string s);
    string getstatus();
    virtual void addUser(User *newUser)=0;
};

#endif // RESOURCE_H

