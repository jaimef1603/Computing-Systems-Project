#include "Degree.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Utilities.h"
#include <cstring>
#include <limits>

using namespace std;

Degree::Degree():name()
{
    vc=nullptr;

}



Degree::Degree(string n, const char *id, VirtualCampus *mycampus)
{
    name=n;
    strncpy(this->id, id, 3);
    this->id[3]='\0';
    vc = mycampus;
}



Degree::~Degree()
{
    for(unsigned i=0;i<stulist.size();i++){
        if (stulist[i]!=nullptr){
            delete stulist[i];
        }
        stulist.erase(stulist.begin()+i);
    }
}




string Degree::getname()
{
    return name;
}



const char* Degree::getid()
{
    return id;
}



VirtualCampus& Degree::getVc()
{
    return *vc;
}



void Degree::setname(string n)
{
    name=n;
}



Menu<Degree>::menu_option_member Degree::gimme_the_name()
{
   return &Degree::name;
}



/* _______________________________________
  |                                       |
  |----------STUDENT FUNCTIONS------------|
  |_______________________________________|
*/



void Degree::addStudent()
{

    string name;
    cout<<"Enter the name of the student: ";
    cin>>name;

    stulist.push_back(new Student(name,this));



    //    Student *temp;
    //    if (stulist==nullptr){
    //        stulist = new Student [1];
    //        stulist[0]=Student(*this);
    //        student_number=1;
    //    }else{
    //        if (student_number>0){
    //            temp=new Student [student_number];
    //            for(int i=0; i<student_number; i++){
    //                temp[i]=stulist[i];
    //            }
    //            delete [] stulist;
    //            stulist = new Student[student_number+1];
    //            for(int i=0; i<student_number; i++){
    //                stulist[i]=temp[i];
    //            }
    //            delete [] temp;
    //            stulist[student_number]=Student(*this);
    //            student_number+=1;
    //        }else{
    //            cerr<<"Degree::addStudent(); Invalid size for student_number.\n"<<endl;
    //        }
    //    }
}



Student* Degree::searchStudentbyid(string id)
{
    for (Student* stu:stulist){
        if (stu->getidentifier()== id){
            return stu;
        }
    }
    return nullptr;
}



void Degree::manageStudents()
{
    char selection='0';
    string buffer;
    int stu;
    do {
        system("clear");
        cout<<"STUDENTS of "<<this->getname()<<":\n";
        showstudents();
        cout<<"1: Create 2: Delete 3: Details 4: Back\n";
        cin>>selection;
        switch(selection){
        case '1':
            selection='0';
            system("clear");
            addStudent();
            (*(stulist.end()-1))->showDetails();
            cin.ignore();
            getchar();
            break;
        case '2':
            selection='0';
            system("clear");
            cout<<"STUDENTS:\n";
            showstudents();
            cout<<"What student do you want to delete? (enter -1 to exit)\n";
            do {
                cin>>ws>>buffer;
                istringstream(buffer)>>stu;
                if ((stu<1 && stu!=-1) || stu >int(stulist.size())){
                    system("clear");
                    cout<<"STUDENTS:\n";
                    showstudents();
                    cout<<"What student do you want to delete? (enter -1 to exit)\n";
                    cout<<"Select a valid number. (1-"<<stulist.size()<<") or -1 to exit.\n \tPress any key to retry.";
                }
            }while((stu<1 && stu!=-1) || stu >int(stulist.size()));
            system("clear");
            if (stu!=-1){
                deleteStudent(unsigned(stu)-1);
            }
            break;
        case '3':
            selection='0';
            system("clear");
            cout<<"STUDENTS:\n";
            showstudents();
            cout<<"What student do you want to show details of? (enter -1 to exit)\n";
            do {
                cin>>ws>>buffer;
                istringstream(buffer)>>stu;
                if ((stu<1 && stu!=-1) || stu >int(stulist.size())){
                    system("clear");
                    cout<<"STUDENTS:\n";
                    showstudents();
                    cout<<"What student do you want to show details of? (Write the number or -1 to exit)\n";
                    cout<<"Select a valid number. (number up to "<<stulist.size()<<") or -1 to exit.\n \tPress any key to retry.";
                }
            }while((stu<1 && stu!=-1) || stu >int(stulist.size()));
            system("clear");
            if (stu!=-1){
                stulist[unsigned(stu)-1]->showDetails();
                cin.ignore(90, '\n');
                getchar();
            }
            break;

        case '4':
            return;
        default:
            cout<<"Enter a valid number(1-4).\n"<<endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            break;
        }
    }while(true);

}



/*
void Degree::showstudents(){
    for (unsigned i=0; i< stulist.size(); i++){
        cout<<i+1;
        cout<<stulist[i]<<endl;
    }
}
*/



void Degree::showstudents()     //Function to show all the students of stulist
{
    for (unsigned i=0; i<stulist.size(); i++){
        cout<<i+1<<": "<<stulist[i]->getSIN()<<endl;

    }
}



vector <Student*>& Degree::getStudents()
{
    return stulist;
}



int Degree::findStudent(string identification)    //Function to find a student in the stulist if it is created, and return the position where it is
{

    for (unsigned i=0; i<stulist.size(); i++){
        if (identification==stulist[i]->getidentifier()){
            return int(i);
        }
    }
    return -1;
}



void Degree::deleteStudent(unsigned index)
{

    if(stulist[index]!=nullptr){
        delete stulist[index];
    }

    stulist.erase(stulist.begin()+index);

    //    Student *temp = new Student [student_number-1];
    //    int j=0;

    //    for (int i = 0; i<student_number; i++){
    //        if (i != index){
    //            temp[j]=stulist[i];
    //            j++;
    //        }
    //    }
    //    student_number -=1;
    //    delete [] stulist;
    //    stulist = new Student [student_number];
    //    for (int i=0; i<student_number; i++){
    //        stulist[i]=temp[i];
    //    }
    //    delete [] temp;
}



/* _______________________________________
  |                                       |
  |---------- COURSE FUNCTIONS------------|
  |_______________________________________|
*/



void Degree::manageCourses ()
{
    char selection;
    string buffer;
    int cour;
    do{
            system("clear");
            cout<<"COURSES of "<<this->getname()<<":\n";
            showcourses();
            cout<<"\n";
            cout<<"1: Create 2: Edit 3: Delete 4: Details 5: Select 6:Back\n";
        cin>>selection;
        switch(selection){
        case '1':
            system("clear");
            addCourse();
            break;
        case '2':
            do {
                system("clear");
                cout<<"COURSES:\n";
                showcourses();
                cout<<"What course do you want to edit?\n";
                cin>>ws>>buffer;
                istringstream(buffer)>>cour;
                if ((cour<1 && cour!=-1 )|| cour > int (courselist.size())){
                    cout<<"Select a valid number. (1-"<<courselist.size()<<") or -1 to exit.\n \tPress any key to retry.";
                    cin>>ws>>buffer;
                    istringstream(buffer)>>cour;
                }
            }while((cour<1 && cour!=-1)|| cour >int (courselist.size()));
            system("clear");
            if(cour!=-1){
                courselist[unsigned(cour)-1]->edit();
            }
            break;
        case '3':
            do {
                system("clear");
                cout<<"COURSES:\n";
                showcourses();
                cout<<"What course do you want to delete?\n";
                cin>>ws>>buffer;
                istringstream(buffer)>>cour;
                if ((cour<1 && cour!=-1 )|| cour >int(courselist.size())){
                    cout<<"Select a valid number. (1-"<<courselist.size()<<") or -1 to exit.\n \tPress any key to retry.";
                    cin.ignore(50, '\n');
                    getchar();
                }
            }while((cour<1 && cour!=-1 ) || cour >int(courselist.size()));
            system("clear");
            if(cour!=-1){
                deleteCourse(unsigned(cour)-1);
            }
            break;
        case '4':
            do {
                system("clear");
                cout<<"COURSES:\n";
                showcourses();
                cout<<"What course do you want to show details of?\n";
                cin>>ws>>buffer;
                istringstream(buffer)>>cour;
                if ((cour<1 && cour!=-1 )|| cour >int(courselist.size())){
                    cout<<"Select a valid number. (1-"<<courselist.size()<<") or -1 to exit.\n \tPress any key to retry.";
                    cin.ignore(50, '\n');
                    getchar();
                }
            }while((cour<1 && cour!=-1 ) || cour >int(courselist.size()));
            system("clear");

            if(cour!=-1){
                cout<<"Details of Course "<<cour<<" of "<<this->getname()<<".\n";
                courselist[unsigned(cour)-1]->showdetails();
                cout<<"\tPress any key to return.\n";
                cin.ignore(50, '\n');
                getchar();
            }

            break;
        case '5':
            do {
                system("clear");
                cout<<"COURSES:\n";
                showcourses();
                cout<<"What course do you want to select?\n";
                cin>>ws>>buffer;
                istringstream(buffer)>>cour;
                if ((cour<1 && cour!=-1 )|| cour >int(courselist.size())){
                    cout<<"Select a valid number. (1-"<<courselist.size()<<") or -1 to exit.\n \tPress any key to retry.";
                    cin.ignore(50, '\n');
                    getchar();
                }
            }while((cour<1 && cour!=-1 ) || cour >int(courselist.size()));
            system("clear");
            if(cour!=-1){
                courselist[unsigned(cour)-1]->options();
            }
            break;

        case '6': return;

        default:
            cout<<"Enter a valid number(1-6).\n"<<endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            break;
        }
    }while (true);
}



vector <Course*> Degree::getCourses()
{
    return courselist;
}



int Degree::findCourse(string identification)     //Function to find a course in the courselist if it is created, and return the position where it is
{

    for (unsigned i=0; i<courselist.size(); i++){
        if (identification==courselist[i]->getIdentification()){
            return int(i);
        }
    }

    return -1;
}



void Degree::addCourse()
{
    string id, name;
    string buffer;
    int credits=0;
    do{
    cout<<"Enter the name of the course: ";
    cin>>ws>>name;
    }while(!checkletters(name));
    do {
        cout<<"New course ID CCCIIII (C=char, I=number) or \"cancel\" to exit: "<<this->id;
        cin>>ws>>id;
        if (id=="cancel"){
            break;
        }
        id=this->id+id;
    }while(!checkResId(id));
    do {
        system("clear");
        cout<<"ID: "<<id<<endl;
        cout<<"\nNew course credits (write \"cancel\" to exit): ";
        cin>>ws>>buffer;
        if (buffer=="cancel"){
            break;
        }
        istringstream(buffer)>>credits;
    }while(credits<1);
    if (id!="cancel" && credits> 0){
        courselist.push_back(new Course(name, id,this,credits));
    }

    //    Course *temp;
    //    if (courselist==nullptr){
    //        courselist = new Course[1];
    //        courselist[0]= Course(id, this, credits);
    //        course_number=1;
    //        std::cerr<<"Course added\n";
    //        getchar();
    //    }else{
    //        if (course_number>0 ){
    //            temp=new Course[course_number];
    //            for(int i=0; i<course_number; i++){
    //                temp[i]=courselist[i];
    //            }
    //            delete [] courselist;
    //            courselist = new Course[course_number+1];
    //            for(int i=0; i<course_number; i++){
    //                courselist[i]=temp[i];
    //            }
    //            delete [] temp;
    //            courselist[course_number]= Course(id, this, credits);
    //            course_number+=1;
    //        }else{
    //            cerr<<"Degree::addCourse(); Invalid value for course_number, new value is 0.\n"<<endl;
    //            course_number=0;
    //        }
    //    }
    system("clear");
}



void Degree::deleteCourse(unsigned index)
{
    if(courselist[index]!=nullptr){
        delete courselist[index];
    }
    courselist.erase(courselist.begin()+index);


    //    Course *temp = new Course [course_number-1];
    //    int j=0;

    //    for (int i = 0; i<course_number; i++){
    //        if (i != index){
    //            temp[j]=courselist[i];
    //            j++;
    //        }
    //    }
    //    course_number -=1;
    //    delete [] courselist;
    //    courselist = new Course [course_number];
    //    for (int i=0; i<course_number; i++){
    //        courselist[i]=temp[i];
    //    }
    //    delete [] temp;
}



void Degree::showcourses()       //Function to show all the courses
{

    cout<<"\t\nCourses:"<<endl;
    for (unsigned i=0; i< courselist.size(); i++){
        cout<<i+1<<":\n";
        cout<<"\tID: "<<courselist[i]->getIdentification();
        cout<<"\tName: "<<courselist[i]->getname();
        cout<<"\tCredits: "<<courselist[i]->getcredits();
        cout<<"\n";
    }

}



void Degree::edit()     //Function to edit degree's attributes (name)
{
    char selection;
    //system("clear");
    //cout<<"1: Edit name 2: Back\n";
    do{
        system("clear");
        cout<<"1: Edit name 2: Back\n";
        cin>>selection;
        switch (selection) {
        case '1':{
            string newname;
            bool valid=false;
            system("clear");
            cout<<"Enter the new name (letters a-z, A-Z) or \"cancel\" to exit\n"<<endl;
            do {
                cin>>ws>>newname;
                if (newname=="cancel"){
                    break;
                }
                if (!(valid=checkletters(newname))){
                    cout<<"Enter a valid name (letters a-z, A-Z) or \"cancel\" to exit\n"<<endl;
                }
            }while (!valid);
            if (valid){
                this->setname(newname);
            }
           break;
        }
        case '2': return;
        default:
            system("clear");
            cout<<"1: Edit name 2: Back\n";
            cout<<"Select a valid number\n";
            break;
        }
    }while(true);

}



void Degree::showdetails()     //Function to show the details of a degree
{
    cout<<"ID: "<<id<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Students: "<<stulist.size()<<endl;
    cout<<"Courses: "<<courselist.size()<<endl;
}



void Degree::options()     //Degree's options
{
    char selection;

    do {
        system("clear");
        cout<<"1: Courses\n2: Students\n3: Back\n";
        cin>>selection;
        switch (selection) {
        case '1':
            system("clear");
            manageCourses();
            break;
        case '2':
            system("clear");
            manageStudents();
            break;
        case '3': return;
        default:
            cout<<"Enter a valid number(1-3).\n"<<endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            break;
        }
    }while(true);
}



//void Degree::editcourse()
//{
//    int selection,field, newcredits;
//    string newid;
//    cout<<"Select the course you want to edit (1-"<<course_number+1<<")"<<endl;
//    for (int i=0; i<course_number; i++){
//        cout<<i+1<<": "<<courselist[i].getIdentification()<<endl;
//    }
//    cin>>selection;
//    do{
//        system("clear");
//        cout<<"Select the field you want to edit (1-2)\n1: id\n2: credits\n"<<endl;
//        cin>>field;
//        switch (field) {
//        case 1:
//            cout<<"Enter the new id: ";
//            cin>>newid;
//            courselist[selection-1].setIdentification(newid);
//            break;
//        case 2:
//            cout<<"Enter the new value for credits: ";
//            cin>>newcredits;
//            courselist[selection-1].setcredits(newcredits);
//            break;
//        default:
//            cout<<"Enter a valid number(1-5).\n\tPress any key to retry.\n"<<endl;
//            getchar();
//            break;
//        }
//    }while(true);
//}
