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

//void User::addCourse(Link_us_res *link){
//    std::cerr<<"This object can't add Course"<<std::endl;
//}
//void User::addSeminar(Link_us_res *link){
//    std::cerr<<"This object can't add Seminar"<<std::endl;
//}
//void User::addFDP(Link_us_res *link){
//    std::cerr<<"This object can't add FDP"<<std::endl;
//}


//char selection;
//do {
//    system ("clear");
//    cout<<"1: Seminars \n2: Courses \n3:FDPs \n4: Back\n";
//    cin>>selection;
//switch (selection) {
//case '1':

//case '2':

//case '3':

//case '4': return;

//default: cout<<"Select a valid number (1-4)\n\tPress any key to retry."<<endl;

//    getchar();
//    break;

//}
//}while(true);
