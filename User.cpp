#include "User.h"
#include <iostream>

User::~User()
{

}



void User::setname(string n)
{
    name=n;
}



string User::getname()
{
    return name;
}



Menu<User>::menu_option_member User::gimmethename()
{
    return &User::name;
}


/* _______________________________________
  |                                       |
  |------------FILE HANDLING--------------|
  |_______________________________________|
*/



ofstream & operator<< (ofstream& ofs, User* _user)
{
    unsigned long length = _user->name.size()+1;
    char *name = nullptr;
    name = new char[length];
    strcpy(name,_user->name.c_str());
    ofs.write(reinterpret_cast<char*>(&(length)), sizeof (unsigned long));
    ofs.write(name,  length * sizeof (char));
    delete [] name;
    return ofs;
}



ifstream & operator>> (ifstream& ifs,User* _user)
{
   unsigned long length;
   ifs.read(reinterpret_cast<char*>(&(length)), sizeof (unsigned long));
   char * name=new char[length];
   ifs.read(name,  static_cast<long>(length * sizeof (char)));
   _user->name=name;
   delete [] name;
   return ifs;
}
