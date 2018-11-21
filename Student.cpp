#include <iostream>
#include <string>
#include <sstream>
#include "Student.h"
#include "Course.h"
#include "Seminar.h"
#include "FDP.h"
using namespace std;
Student::Student(int id):mycourses(), myseminars(){
    SIN=id;
    mydegree=nullptr;
    myfdp=nullptr;
}


Student::Student(int id, Degree &d):mycourses(), myseminars(){
    SIN=id;
    mydegree=&d;
    myfdp=nullptr;
}


Student::Student (const Student &s){
    mycourses=s.mycourses;  //cambiar cuando el constructor de copia de ArrayList este hecho.
    myseminars=s.myseminars; // " " "
    SIN=s.SIN;
    mydegree=s.mydegree;
    myfdp=s.myfdp;
}


Student& Student::operator=(const Student &s){
    if(s.SIN==0 || s.mydegree==nullptr){
        cerr<<"Student::operator=: Some of the atributes are invalid\n";
    }
    mycourses=s.mycourses;
    myseminars=s.myseminars;
    SIN=s.SIN;
    mydegree=s.mydegree;
    myfdp=s.myfdp;

    return *this;

}



int Student::getSIN(){
    return SIN;
}



void Student::setSIN(int s){
    SIN=s;
}



string Student::getidentifier(){
    string ident = "";

    ident = static_cast<ostringstream*>(&(ostringstream() << SIN))->str();

    return ident;
    //convertir a string el SIN (es int) y retornar el resultado
}



void Student::Drop(Course *c)
{
   Link_stu_res link (this, c);
   for (int i=0; i<mycourses.getsize(); i++){
       if (*mycourses[i]==link){
           mycourses[i]->destroy();
       }
   }
}



void Student::Drop(Seminar *s)
{
    Link_stu_res link (this, s);
    for (int i=0; i<myseminars.getsize(); i++){
        if (*myseminars[i]==link){
            myseminars[i]->destroy();
        }
    }
}



void Student::Dropfdp()
{
    if (myfdp!= nullptr){
        myfdp->destroy();
    }
}



int Student::menu(){

}

/*
 *
 *
 *
 */
void Student::addCourse(Link_stu_res *link){
    mycourses.pushFront(link);
}
void Student::addSeminar(Link_stu_res *link){
   myseminars.pushFront(link);
}
void Student::addFDP(Link_stu_res *link){
    if(myfdp==nullptr){
        myfdp=link;
    }
}



void Student::removeCourse(Link_stu_res *link)
{
    mycourses.remove(link);
}



void Student::enroll(Resource *res){

    //Link_us_res link = res->addUser(this);
    //mycourses.pushFront(res->addUser(this));


    //Link_us_res *Link = new Link_us_res(this, res);

     //Provisional!!!! hay que hacer comprobaciones previas y manejar excepciones

    //return

}


ostream& operator<<(ostream& os, const Student& stu){
    os<<stu.SIN<<endl;
    return os;
}

