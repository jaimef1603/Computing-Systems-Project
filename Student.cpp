#include <iostream>
#include <string>
#include <sstream>
#include "Student.h"
#include "Course.h"
#include "Seminar.h"
#include "FDP.h"



using namespace std;

int Student::count;

Student::Student():mycourses(), myseminars()
{
    SIN=1000000 + count;
    mydegree=nullptr;
    myfdp=nullptr;
    count+=1;
}



Student::Student(Degree *d):mycourses(), myseminars()
{
    SIN=1000000 + count;
    mydegree=d;
    myfdp=nullptr;
    count+=1;
}



Student::Student (const Student &s)
{
    mycourses=s.mycourses;  //cambiar cuando el constructor de copia de ArrayList este hecho.
    myseminars=s.myseminars; // " " "
    SIN=s.SIN;
    mydegree=s.mydegree;
    myfdp=s.myfdp;
}



Student::~Student()
{
    for (int i = mycourses.getsize()-1; i>=0; i-- ){
       delete mycourses[i];
    }
    for (int i = myseminars.getsize()-1; i>=0; i--){
        delete myseminars[i];
    }
    if (myfdp!=nullptr){
        delete myfdp;
    }
}



Student& Student::operator=(const Student &s)
{
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



void Student::setCount(int c)
{
    count = c;
}



int Student::getCount()
{
    return count;
}



int Student::getSIN(){
    return SIN;
}



void Student::setSIN(int s)
{
    SIN=s;
}



string Student::getidentifier()
{
    string ident = "";

    ident = static_cast<ostringstream*>(&(ostringstream() << SIN))->str();
    if (ident.length()<7){

        for(unsigned i=0; i<(7-ident.length()); i++){
            ident="0"+ident;
        }
    }
    return ident;
    //convertir a string el SIN (es int) y retornar el resultado
}



void Student::showDetails()
{
   cout<<"SIN: "<<getidentifier();
   cout<<"  Courses enrolled: "<<mycourses.getsize();
   cout<<"  Seminars enrolled: "<<myseminars.getsize();
   cout<<"  Has FDP: ";
   if(myfdp!=nullptr){
       cout<<"YES"<<endl;
   }else{
       cout<<"NO"<<endl;
   }
}




void Student::Drop(Course *c)
{
   Link_stu_res link (this, c);
   for (int i=0; i<mycourses.getsize(); i++){
       if (*mycourses[i]==link){
           delete mycourses[i];
       }
   }
}



void Student::Drop(Seminar *s)
{
    Link_stu_res link (this, s);
    for (int i=0; i<myseminars.getsize(); i++){
        if (*myseminars[i]==link){
            delete myseminars[i];
        }
    }
}



void Student::Dropfdp()
{
    if (myfdp!= nullptr){
        delete myfdp;
    }
}



int Student::menu(){

}



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



void Student::removeResource(Link_stu_res *link)
{
    int flag = mycourses.remove(link) + myseminars.remove(link);
    if (myfdp==link){
        myfdp=nullptr;
    }else if(flag==0){
        cerr<<"Student::removeResource(Link_stu_res*); Nothing to remove.\n";
    }

}



void Student::enroll(Course *cour)
{

    Link_stu_res *newLink = new Link_stu_res(this, cour);

    newLink->connectStutoCourse();
    newLink->connectResource();

}



void Student::enroll(Seminar *setminar)
{
    Link_stu_res *newLink = new Link_stu_res(this, setminar);

    newLink->connectStutoSeminar();
    newLink->connectResource();
}


void Student::enroll(FDP *project)
{
    Link_stu_res *newLink = new Link_stu_res(this, project);

    newLink->connectStutoFDP();
    newLink->connectResource();

}


ostream& operator<<(ostream& os, const Student& stu){
    os<<stu.SIN<<endl;
    return os;
}

