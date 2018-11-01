#include <iostream>
#include <string>
#include <sstream>
#include "Student.h"
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

void Student::menu(){

}

/*
 *
 *
 *
 */
void Student::addCourse(Link_us_res *link){
    mycourses.pushFront(link);
}
void Student::addSeminar(Link_us_res *link){
   myseminars.pushFront(link);
}
void Student::addFDP(Link_us_res *link){
    if(myfdp==nullptr){
        myfdp=link;
    }
}

void Student::enroll(Resource *res){

    Link_us_res link = res->addUser(this);
    mycourses.pushFront(res->addUser(this));


    //Link_us_res *Link = new Link_us_res(this, res);

     //Provisional!!!! hay que hacer comprobaciones previas y manejar excepciones

    //return

}

