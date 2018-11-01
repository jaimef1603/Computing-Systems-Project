#include "Degree.h"
#include <iostream>
#include <string>
using namespace std;

Degree::Degree():name(){
   student_number=course_number=fdp_number=0;
   stulist=nullptr;
   courselist=nullptr;
   projectlist=nullptr;
}

Degree::Degree(string n){
   student_number=course_number=fdp_number=0;
   name=n;
   stulist=nullptr;
   courselist=nullptr;
   projectlist=nullptr;
}

string Degree::getname(){
    return name;
}
void Degree::setname(string n){
    name=n;
}

void Degree::addCourse(){

}
void Degree::addStudent(){
    int id;
    cout<<"Write new student id"<<endl;
    cin>>id;
    Student *temp;
    if (stulist==nullptr){
        stulist = new Student(id, *this);
    }else{
        if (student_number>0){
            temp=new Student [student_number];
            for(int i=0; i<student_number; i++){
                temp[i]=stulist[i];
            }
        }else{
            cerr<<"invalid size for student_number"<<endl;
        }
    }
}
void addFDP();
