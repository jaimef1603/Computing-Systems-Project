#include "Degree.h"
#include <iostream>
#include <string>


using namespace std;



Degree::Degree():name(){
    student_number=course_number=0;
    stulist=nullptr;
    courselist=nullptr;

}



Degree::Degree(string n){
    student_number=course_number=0;
    name=n;
    stulist=nullptr;
    courselist=nullptr;
}



Degree::~Degree(){
    if (stulist!=nullptr){
        delete[] stulist;
    }
}


int Degree::getstudent_number(){
    return student_number;
}



string Degree::getname(){
    return name;
}



Student* Degree::searchStudentbyid(string id){
    for (int i=0; i<student_number; i++){
        if (stulist[i].getidentifier()== id){
            return stulist+i;
        }
    }
    return nullptr;
}



void Degree::setname(string n){
    name=n;
}



void Degree::addCourse(){
    string id;
    int credits;
    cout<<"Write new course id:\n"<<endl;
    cin>>ws>>id;
    cout<<"Write the number of credits:\n";
    cin>>ws>>credits;
    Course *temp;
    if (courselist==nullptr){
        courselist = new Course[1];
        courselist[0]= Course(id, this, credits);
        course_number=1;
        std::cerr<<"Course added\n";
        getchar();
    }else{
        if (course_number>0 ){
            temp=new Course[course_number];
            for(int i=0; i<course_number; i++){
                temp[i]=courselist[i];
            }
            delete [] courselist;
            courselist = new Course[course_number+1];
            for(int i=0; i<course_number; i++){
                courselist[i]=temp[i];
            }
            delete [] temp;
            courselist[course_number]= Course(id, this, credits);
            course_number+=1;
        }else{
            cerr<<"Degree::addCourse(); Invalid value for course_number, new value is 0.\n"<<endl;
            course_number=0;
        }
    }
}



void Degree::editcourse()
{
    int selection,field, newcredits;
    string newid;
    cout<<"Select the course you want to edit (1-"<<course_number+1<<")"<<endl;
    for (int i=0; i<course_number; i++){
        cout<<i+1<<": "<<courselist[i].getIdentification()<<endl;
    }
    cin>>selection;
    system("clear");
    cout<<"Select the field you want to edit (1-2)\n1: id\n2: credits\n"<<endl;
    cin>>field;
    switch (field) {
    case 1:
        cout<<"Enter the new id: ";
        cin>>newid;
        courselist[selection-1].setIdentification(newid);
        break;
    case 2:
        cout<<"Enter the new value for credits: ";
        cin>>newcredits;
        courselist[selection-1].setcredits(newcredits);
        break;
    }

}



void Degree::addStudent(){
    int id;
    cout<<"Write new student id"<<endl;
    cin>>ws>>id;
    Student *temp;
    if (stulist==nullptr){
        stulist = new Student(id, *this);
        student_number=1;
    }else{
        if (student_number>0){
            temp=new Student [student_number];
            for(int i=0; i<student_number; i++){
                temp[i]=stulist[i];
            }
            delete [] stulist;
            stulist = new Student[student_number+1];
            for(int i=0; i<student_number; i++){
                stulist[i]=temp[i];
            }
            delete [] temp;
            student_number+=1;
        }else{
            cerr<<"Degree::addStudent(); Invalid size for student_number.\n"<<endl;
        }
    }
}



void Degree::showstudents(){
    for (int i=0; i< student_number; i++){
        cout<<stulist[i];
    }
}



void Degree::showcourses(){
    if (courselist!=nullptr){
        cout<<"\t\nCourses:"<<endl;
        for (int i=0; i< course_number; i++){
            cout<<"\tid: "<<courselist[i].getIdentification();
            cout<<"\tCredits: "<<courselist[i].getcredits();
        }
    }
}
