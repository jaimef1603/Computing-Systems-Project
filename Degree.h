#ifndef DEGREE_H
#define DEGREE_H
#include <string>
using namespace std;


class Degree
{
private:
    string name;
public:
    Degree();
    string getname();
    void setname(string n);
};

#endif // DEGREE_H
