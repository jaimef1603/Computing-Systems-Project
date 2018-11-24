#include "Degree.h"
#include <iostream>
#include <string>
#include "Utilities.h"
#include <cstring>

using namespace std;



Degree::Degree():name(){
    student_number=course_number=0;
    stulist=nullptr;
    courselist=nullptr;
    vc=nullptr;

}



Degree::Degree(string n, const char *id, VirtualCampus *mycampus){
    student_number=course_number=0;
    name=n;
    stulist=nullptr;
    courselist=nullptr;
    strncpy(this->id, id, 3);
    this->id[3]='\0';
    vc = mycampus;
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



char& Degree::getid(){
    return *id;
}



VirtualCampus& Degree::getVc()
{
    return *vc;
}



Student* Degree::searchStudentbyid(string id)
{
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



void Degree::edit()
{
    int selection;
    do{
        system("clear");
        cout<<"1: Edit name 2: exit\n";
        cin>>selection;
    }while(selection !=1 && selection != 2);
    switch (selection) {
    case 1:{
        string newname;
        cout<<"Enter the new name"<<endl;
        cin>>newname;
        this->setname(newname);
    }; break;
    case 2: return;
    }


}



void Degree::addCourse(){
    string id;
    int credits;
    cout<<"Write new course id:\n";
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
    system("clear");
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



void Degree::deleteCourse(int index)
{
    Course *temp = new Course [course_number-1];
    int j=0;

    for (int i = 0; i<course_number; i++){
        if (i != index){
            temp[j]=courselist[i];
            j++;
        }
    }
    course_number -=1;
    delete [] courselist;
    courselist = new Course [course_number];
    for (int i=0; i<course_number; i++){
        courselist[i]=temp[i];
    }
    delete [] temp;
}



void Degree::addStudent(){
    Student *temp;
    if (stulist==nullptr){
        stulist = new Student [1];
        stulist[0]=Student(*this);
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
            stulist[student_number]=Student(*this);
            student_number+=1;
        }else{
            cerr<<"Degree::addStudent(); Invalid size for student_number.\n"<<endl;
        }
    }
}



void Degree::deleteStudent(int index)
{
    Student *temp = new Student [student_number-1];
    int j=0;

    for (int i = 0; i<student_number; i++){
        if (i != index){
            temp[j]=stulist[i];
            j++;
        }
    }
    student_number -=1;
    delete [] stulist;
    stulist = new Student [student_number];
    for (int i=0; i<student_number; i++){
        stulist[i]=temp[i];
    }
    delete [] temp;
}



void Degree::showstudents(){
    for (int i=0; i< student_number; i++){
        cout<<stulist[i];
    }
}




Student* Degree::getStudents()
{
    return stulist;
}



int Degree::findStudent(string identification)
{
    if(stulist!=nullptr){
        for (int i=0; i<student_number; i++){
            if (identification==stulist[i].getidentifier()){
                return i;
            }
        }
    }
    return -1;
}



void Degree::showcourses()
{
    if (courselist!=nullptr){
        cout<<"\t\nCourses:"<<endl;
        for (int i=0; i< course_number; i++){
            cout<<"\tid: "<<courselist[i].getIdentification();
            cout<<"\tCredits: "<<courselist[i].getcredits();
            cout<<"\n";
        }
    }
}



Course* Degree::getCourses()
{
    return courselist;
}



int Degree::findCourse(string identification)
{
    if(courselist!=nullptr){
        for (int i=0; i<course_number; i++){
            if (identification==courselist[i].getIdentification()){
                return i;
            }
        }
    }
    return -1;
}



void Degree::showdetails()
{
    cout<<"Name: "<<name<<endl;
    cout<<"Students: "<<student_number<<endl;
    cout<<"Courses: "<<course_number<<endl;
}



void Degree::options()
{
    int selection;
    cout<<"1: Courses\n2: Students\n3: Back\n";
    do {
        cin>>selection;
        if (selection <1 || selection >3){
            system("clear");
            cout<<"1: Courses\n2: Students\n3: Back\n";
            cout<<"Select a valid number (1-3)"<<endl;
        }
    }while(selection <1 || selection >3);
    switch (selection) {
    case 1:
        system("clear");
        manageCourses();
        break;
    case 2:
        system("clear");
        manageStudents();
        break;
    case 3: break;
    }
    return;
}



void Degree::manageCourses ()
{


    int selection, cour;
    do{
        system("clear");
        cout<<"COURSES of "<<this->getname()<<":\n";
        showcourses();
        cout<<"\n";
        cout<<"1: Create 2: Edit 3: Delete 4:Details 5: Select 6:Back\n";
        cin>>selection;
        switch(selection){
        case 1:
            system("clear");
            addCourse();
            break;
        case 2:
            do {
                system("clear");
                cout<<"COURSES:\n";
                showcourses();
                cout<<"What course do you want to edit?\n";
                cin>>ws>>cour;
                if ((cour<1 && cour!=-1 )|| cour >course_number){
                    cout<<"Select a valid number. (1-"<<course_number<<") or -1 to exit.\n \tPress any key to retry.";
                    getchar();
                }
            }while((cour<1 && cour!=-1)|| cour >course_number);
            system("clear");
            if(cour!=-1){
                courselist[cour-1].edit();
            }
            break;
        case 3:
            do {
                system("clear");
                cout<<"COURSES:\n";
                showcourses();
                cout<<"What course do you want to delete?\n";
                cin>>ws>>cour;
                if ((cour<1 && cour!=-1 )|| cour >course_number){
                    cout<<"Select a valid number. (1-"<<course_number<<") or -1 to exit.\n \tPress any key to retry.";
                    getchar();
                }
            }while((cour<1 && cour!=-1 ) || cour >course_number);
            system("clear");
            if(cour!=-1){
                deleteCourse(cour-1);
            }
            break;
        case 4:
            do {
                system("clear");
                cout<<"COURSES:\n";
                showcourses();
                cout<<"What course do you want to show details of?\n";
                cin>>ws>>cour;
                if ((cour<1 && cour!=-1 )|| cour >course_number){
                    cout<<"Select a valid number. (1-"<<course_number<<") or -1 to exit.\n \tPress any key to retry.";
                    getchar();
                }
            }while((cour<1 && cour!=-1 ) || cour >course_number);
            system("clear");

            if(cour!=-1){
                cout<<"Details of Course "<<cour<<"of "<<this->getname()<<".\n";
                courselist[cour-1].showdetails();
                cout<<"\tPress any key to close.\n";
                cin.ignore(1, '\n');
                getchar();
            }

            break;
        case 5:
            do {
                system("clear");
                cout<<"COURSES:\n";
                showcourses();
                cout<<"What course do you want to select?\n";
                cin>>ws>>cour;
                if ((cour<1 && cour!=-1 )|| cour >course_number){
                    cout<<"Select a valid number. (1-"<<course_number<<") or -1 to exit.\n \tPress any key to retry.";
                    getchar();
                }
            }while((cour<1 && cour!=-1 ) || cour >course_number);
            system("clear");
            if(cour!=-1){
                courselist[cour-1].options();
            }
            break;

        case 6: return;

        default: cout<<"Enter a valid number(1-5).\n\tPress any key to retry.\n"<<endl;
            getchar();
            break;
        }
    }while (true);
}




void Degree::manageStudents()
{

    int selection, stu;
    do {
        system("clear");
        cout<<"STUDENTS of "<<this->getname()<<":\n";
        showstudents();
        cout<<"1: Create 2: Delete 3: Details 4: Back\n";
        cin>>selection;
        switch(selection){
        case 1:
            addStudent();
            this->stulist->showDetails();
            cin.ignore(1,'\n');
            getchar();
            break;
        case 2:
            do {
                system("clear");
                cout<<"STUDENTS:\n";
                showstudents();
                cout<<"What student do you want to delete?\n";
                cin>>ws>>stu;
                if ((stu<1 && stu!=-1) || stu >student_number){
                    cout<<"Select a valid number. (1-"<<student_number<<") or -1 to exit.\n \tPress any key to retry.";
                    getchar();
                }
            }while((stu<1 && stu!=-1) || stu >student_number);
            system("clear");
            deleteStudent(stu-1);
            break;
        case 3:
            do {
                system("clear");
                cout<<"STUDENTS:\n";
                showstudents();
                cout<<"What student do you want to show details of?\n";
                cin>>ws>>stu;
                if ((stu<1 && stu!=-1) || stu >student_number){
                    cout<<"Select a valid number. (1-"<<student_number<<") or -1 to exit.\n \tPress any key to retry.";
                    getchar();
                }
            }while((stu<1 && stu!=-1) || stu >student_number);
            system("clear");
            stulist[stu-1].showDetails();
            cin.ignore(1, '\n');
            getchar();
            break;

        case 4: return;
        default: cout<<"Enter a valid number(1-4).\n\tPress any key to retry."<<endl;
            getchar();
            break;
        }
    }while(true);

}
