#include "Degree.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Utilities.h"
#include <cstring>
#include <limits>
#include "Student.h"

using namespace std;

Degree::Degree():name()
{
    vc=nullptr;

}



Degree::Degree(VirtualCampus *mycampus, string n, const char *id)
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

    char name[40];
    cout<<"Enter the name of the student or \'q\' to cancel: ";
    cin.ignore(numeric_limits<char>::max(), '\n');
    cin.getline(name, 50);
    if(name=="q"){
        return;
    }
    Student *there_is_a_new_face_in_class = new Student(this, name);
    stulist.push_back(there_is_a_new_face_in_class);
    there_is_a_new_face_in_class->showDetails();

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
        cout<<"\n\t[1] Create\n \t[2] Delete\n \t[3] Details\n \t'q' Back\n";
        cin>>selection;
        switch(selection){
        case '1':
            selection='0';
            system("clear");
            addStudent();
            cin.ignore();
            getchar();
            break;
        case '2':
            selection='0';
            do {
                system("clear");
                cout<<"STUDENTS:\n";
                showstudents();
                cout<<"What student do you want to delete? (enter \'q\' to cancel)\n";
                cin>>ws>>buffer;

                if(buffer=="q"){
                    return;
                }

                istringstream(buffer)>>stu;
                if (stu >int(stulist.size())){
                    system("clear");
                    cout<<"STUDENTS:\n";
                    showstudents();
                    cout<<"What student do you want to delete? (enter \'q\' to cancel)\n";
                    cout<<"Select a valid number. (1-"<<stulist.size()<<") or \'q\' to cancel.\n \tPress any key to retry.";
                }
            }while(stu >int(stulist.size()));
            system("clear");
            if (stu!='q'){
                deleteStudent(unsigned(stu)-1);
            }
            break;
        case '3':{
            char willyouedit;
            selection='0';

            do {
                system("clear");
                cout<<"STUDENTS:\n";
                showstudents();
                cout<<"What student do you want to show details of? (enter \'q\' to cancel)\n";
                cin>>ws>>buffer;

                if(buffer=="q"){
                    return;
                }

                istringstream(buffer)>>stu;
                if (stu >int(stulist.size())){
                    system("clear");
                    cout<<"STUDENTS:\n";
                    showstudents();
                    cout<<"What student do you want to show details of? (enter \'q\' to cancel)\n";
                    cout<<"Select a valid number. (1-"<<stulist.size()<<") or \'q\' to cancel.\n \tPress any key to retry.";
                }
            }while(stu >int(stulist.size()));
            system("clear");
            if (stu!='q'){

                do {
                    system("clear");
                    if (!cin.good()){
                        cin.clear();
                        cin.ignore(numeric_limits<char>::max(), '\n');
                    }
                    stulist[unsigned(stu)-1]->showDetails();
                    cout<<"\t[1] Edit Name\n\t \'q\' Back "<<endl;
                    cin>>ws>>willyouedit;
                }while(!cin.good() && willyouedit!='q' && willyouedit!='1');

                //!cin.good() ||

                if (willyouedit == 'q'){
                    break;
                }else{
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    do {
                        system("clear");
                        if (!cin.good()){
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cout<<"Enter the new name or \'q\' to cancel: ";

                    }while(!getline(cin, buffer, '\n') || !checkletters(buffer));

                    if (buffer!="q"){
                        stulist[unsigned(stu)-1]->setname(buffer);
                    }
                }
            }
        }
            break;

        case 'q':
            return;
        default:
            cout<<"Enter a valid number(1-3) or \'q\' to cancel.\n"<<endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }
    }while(true);

}



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
        cout<<"\t[1] Create\n \t[2] Edit\n \t[3] Delete\n \t[4] Details\n \t[5] Select\n \t'q' Back\n";
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
                cout<<"What course do you want to edit? (Enter (1-"<< courselist.size()<<")to edit or \'q\' to cancel)\n";
                cin>>ws>>buffer;

                if(buffer=="q"){
                    return;
                }

                istringstream(buffer)>>cour;
                if (cour > int (courselist.size())){
                    cout<<"Select a valid number. (1-"<<courselist.size()<<") or \'q\' to cancel.\n \tPress any key to retry.";
                    cin>>ws>>buffer;

                    if(buffer=="q"){
                        return;
                    }

                    istringstream(buffer)>>cour;
                }
            }while(cour >int (courselist.size()));
            system("clear");
            if(cour!='q'){
                courselist[unsigned(cour)-1]->edit();
            }
            break;
        case '3':
            do {
                system("clear");
                cout<<"COURSES:\n";
                showcourses();
                cout<<"What course do you want to delete? (Enter (1-"<< courselist.size()<<")to edit or \'q\' to cancel)\n";
                cin>>ws>>buffer;

                if(buffer=="q"){
                    return;
                }

                istringstream(buffer)>>cour;
                if (cour >int(courselist.size())){
                    cout<<"Select a valid number. (1-"<<courselist.size()<<") or \'q\' to cancel.\n \tPress any key to retry.";
                    cin.ignore(50, '\n');
                    getchar();
                }
            }while(cour >int(courselist.size()));
            system("clear");
            if(cour!='q'){
                deleteCourse(unsigned(cour)-1);
            }
            break;
        case '4':
            do {
                system("clear");
                cout<<"COURSES:\n";
                showcourses();
                cout<<"What course do you want to show details of?(Enter (1-"<< courselist.size()<<")to edit or \'q\' to cancel )\n";
                cin>>ws>>buffer;

                if(buffer=="q"){
                    return;
                }

                istringstream(buffer)>>cour;
                if (cour >int(courselist.size())){
                    cout<<"Select a valid number. (1-"<<courselist.size()<<") or \'q\' to cancel.\n \tPress any key to retry.";
                    cin.ignore(50, '\n');
                    getchar();
                }
            }while(cour >int(courselist.size()));
            system("clear");

            if(cour!='q'){
                cout<<"Details of Course "<<cour<<" of "<<this->getname()<<".\n";
                courselist[unsigned(cour)-1]->showDetails();
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
                cout<<"What course do you want to select?(Enter (1-"<< courselist.size()<<")to edit or \'q\' to cancel)\n";
                cin>>ws>>buffer;

                if(buffer=="q"){
                    return;
                }

                istringstream(buffer)>>cour;
                if (cour >int(courselist.size())){
                    cout<<"Select a valid number. (1-"<<courselist.size()<<") or \'q\' to cancel.\n \tPress any key to retry.";
                    cin.ignore(50, '\n');
                    getchar();
                }
            }while(cour >int(courselist.size()));
            system("clear");
            if(cour!='q'){
                courselist[unsigned(cour)-1]->options();
            }
            break;

        case 'q': return;

        default:
            cout<<"Enter a valid number(1-5) or \'q\' to cancel.\n"<<endl;
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
    bool valid;
    string id;
    char name[40];
    string buffer;
    int credits=0;
    do{
        system("clear");
        cout<<"Enter the name of the course (letters a-z, A-Z) or \'q\' to cancel : ";
        cin.ignore(numeric_limits<char>::max(), '\n');
        cin.getline(name, 50);
        if(name=="q"){
            return;
        }
    }while(!checkletters(name));
    do {
        system("clear");
        valid = true;
        cout<<"New course ID CCCIIII (C=char, I=number) or \'q\' to cancel: "<<this->id;
        cin>>ws>>id;
        if (id=="q"){
            return;
        }
        id=this->id+id;

        if (!checkResId(id)){       //we check if the id is correct (LLLNNNN) or not
            valid = false;          //if it is not correct, we say that valid is false
        }else{                      //if we get here, valid is true so we check if there is already a course with that identification or not
            for (auto it: courselist){
                if (it->getIdentification()==id){
                    valid = false;                        // if there ir, we say that valid is false
                    cout<<"There is already a course with this identification, choose another"<<endl;
                    cin.ignore(numeric_limits<char>::max(), '\n');
                    cin.get();
                }

            }

        }

    }while(!valid);             //we do this until the identification is correct and the identification is not used by any other course
    do {
        system("clear");
        cout<<"ID: "<<id<<endl;
        cout<<"\nNew course credits or \'q\' to cancel: ";
        cin>>ws>>buffer;
        if (buffer=="q"){
            break;
        }
        istringstream(buffer)>>credits;
    }while(credits<1);
    if (id!="q" && credits> 0){
        courselist.push_back(new Course(this, name, id,credits));
    }

    system("clear");
}



void Degree::deleteCourse(unsigned index)
{
    if(courselist[index]!=nullptr){
        delete courselist[index];
    }
    courselist.erase(courselist.begin()+index);

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

    do{
        system("clear");
        cout<<"\t[1] Edit name\n\t 'q' Back\n";
        cin>>selection;
        switch (selection) {
        case '1':{
            char newname[40];
            bool valid=false;

            do {
                system("clear");
                cout<<"Enter the new name (letters a-z, A-Z) or \'q\' to cancel"<<endl;
                cin.ignore(numeric_limits<char>::max(), '\n');
                cin.getline(newname, 50);
                if (newname=="q"){
                    break;
                }
                                                               //checkletters returns true if the name characters are only letters
                if (!(valid=checkletters(newname))){           //and false if there is a character that is not a letter
                    cout<<"Enter a valid name (letters a-z, A-Z) or \'q\' to exit\n"<<endl;
                }
            }while (!valid);       //we do this until the name characters are only letters
            if (valid){
                this->setname(newname);
            }
            break;
        }
        case 'q': return;
        default:
            system("clear");
            cout<<"\t[1] Edit name\n\t 'q' Back\n";
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
        cout<<"Degree options\n"<<endl;
        cout<<"\t[1] Courses\n \t[2] Students\n \t'q' Back\n";
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
        case 'q': return;
        default:
            cout<<"Enter a valid number(1-3).\n"<<endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            break;
        }
    }while(true);
}



//---------- FILE HANDLING-----------------

#include "DegreeFiles.tpp"
