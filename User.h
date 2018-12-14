#ifndef USER_H
#define USER_H
#include <string.h>
#include <iostream>
#include "Menu.h"
#include <fstream>

using namespace std;


class Link_us_res;

class User
{
protected:
    string name;
public:
    virtual ~User();
    virtual void menu()=0;
    virtual std::string getidentifier()=0;
    void setname(string n);
    string getname();
    static Menu<User>::menu_option_member gimmethename();


    //FILE HANDLING

    friend ofstream & operator<< (ofstream& ofs, User* _user);
    friend ifstream & operator>> (ifstream& ifs, User* _user);
};

#endif // USER_H
