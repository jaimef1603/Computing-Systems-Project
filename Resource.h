#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
using namespace std;

class Resource
{
protected:
    string ID;
    string status;
public:
    Resource();
    void setID (string i);
    string getID();
    void setstatus(string s);
    string getstatus();
};

#endif // RESOURCE_H

