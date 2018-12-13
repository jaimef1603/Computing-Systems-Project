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

    string name;
    cout<<"Enter the name of the student or \'q\' to cancel: ";
    cin>>name;
    if(name=="q"){
        return;
    }
    stulist.push_back(new Student(this, name));



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
        cout<<"\n\t[1] Create\n \t[2] Delete\n \t[3] Details\n \t'q' Back\n";
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
                if ((stu<1 && stu!=-1) || stu >int(stulist.size())){
//                    system("clear");
//                    cout<<"STUDENTS:\n";
//                    showstudents();
//                    cout<<"What student do you want to delete? (\'q\' to cancel)\n";
                    cout<<"Select a valid number. (1-"<<stulist.size()<<") or \'q\' to cancel.\n \tPress any key to retry.";
                }
            }while((stu<1 && stu!=-1) || stu >int(stulist.size()));
            system("clear");
            if (stu!=-1){
                deleteStudent(unsigned(stu)-1);
            }
            break;
        case '3':
            selection='0';
            do {
                system("clear");
                cout<<"STUDENTS:\n";
                showstudents();
                cout<<"What student do you want to show details of? (\'q\' to cancel)\n";
                cin>>ws>>buffer;
                if(buffer=="q"){
                    return;
                }
                istringstream(buffer)>>stu;
                if ((stu<1 && stu!=-1) || stu >int(stulist.size())){
//                    system("clear");
//                    cout<<"STUDENTS:\n";
//                    showstudents();
//                    cout<<"What student do you want to show details of? (Write the number or \'q\' to cancel)\n";
                    cout<<"Select a valid number. (number up to "<<stulist.size()<<") or \'q\' to cancel.\n \tPress any key to retry.";
                }
            }while((stu<1 && stu!=-1) || stu >int(stulist.size()));
            system("clear");
            if (stu!=-1){
                stulist[unsigned(stu)-1]->showDetails();
                cin.ignore(90, '\n');
                getchar();
            }
            break;

        case 'q':
            return;
        default:
            cout<<"Enter a valid number(1-3) or \'q\' to cancel.\n"<<endl;
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
                if ((cour<1 && cour!=-1 )|| cour > int (courselist.size())){
                    cout<<"Select a valid number. (1-"<<courselist.size()<<") or \'q\' to cancel.\n \tPress any key to retry.";
                    cin.ignore(50, '\n');
                    getchar();
 //                    cin>>ws>>buffer;
//                    if(buffer=="q"){
//                        return;
//                    }
//                    istringstream(buffer)>>cour;
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
                cout<<"What course do you want to delete? (Enter (1-"<< courselist.size()<<")to edit or -1 to exit)\n";
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
                cout<<"What course do you want to show details of?(Enter (1-"<< courselist.size()<<")to edit or -1 to exit)\n";
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

        case 'q': return;

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
    bool valid;
    string id, name;
    string buffer;
    int credits=0;
    do{
        system("clear");
        cout<<"Enter the name of the course (letters a-z, A-Z) or \'q\' to cancel: ";
        cin>>ws>>name;
        if(name=="q"){
            return;
        }
    }while(!checkletters(name));
    do {
        valid = true;
        system("clear");
        cout<<"New course ID CCCIIII (C=char, I=number) or \'q\' to cancel: "<<this->id;
        cin>>ws>>id;
        if (id=="q"){
            return;
        }
        id=this->id+id;

        if (!checkResId(id)){
            valid = false;
            system("clear");
        }else{
            for (auto it: courselist){
                if (it->getIdentification()==id){
                    valid = false;
                    cout<<"There is already a course with this identification, choose another"<<endl;
                    cin.ignore(numeric_limits<char>::max(), '\n');
                    cin.get();
                }

            }

        }


    }while(!valid);
    do {
        system("clear");
        cout<<"ID: "<<id<<endl;
        cout<<"\nNew course credits (write \'q\' to cancel): ";
        cin>>ws>>buffer;
        if (buffer=="q"){
            break;
        }
        istringstream(buffer)>>credits;
    }while(credits<1);
    if (id!="cancel" && credits> 0){
        courselist.push_back(new Course(this, name, id,credits));
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

    //cout<<"\t\nCourses:"<<endl;
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
        cout<<"Edit degree\n"<<endl;
        cout<<"\t[1] Edit name\n\t'q' Back\n";
        cin>>selection;
        switch (selection) {
        case '1':{
            string newname;
            bool valid=false;
            do {
                system("clear");
                cout<<"Enter the new name (letters a-z, A-Z) or \'q\' to cancel"<<endl;
                cin>>ws>>newname;
                if (newname=="q"){
                    break;
                }
                if (!(valid=checkletters(newname))){
                    cout<<"Enter a valid name (letters a-z, A-Z) or \'q\' to cancel\n"<<endl;
                }
            }while (!valid);
            if (valid){
                this->setname(newname);
            }
            break;
        }
        case 'q': return;
        default:
            system("clear");
            //cout<<"\t[1] Edit name\n\t'q' Back\n";
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


 ofstream & operator<< (ofstream& ofs, Degree& _degree)
{
     unsigned long length = _degree.name.size();
     const char *name = _degree.name.c_str();
     ofs.write(reinterpret_cast<char*>(&(length)), sizeof (unsigned long));
     ofs.write(name,  static_cast<long>(length * sizeof (char)));
     ofs.write(_degree.id,  4 * sizeof (char));
     unsigned long student_number = _degree.stulist.size();
     unsigned long course_number = _degree.courselist.size();
     ofs.write(reinterpret_cast<char*>(&student_number), sizeof (unsigned long));
     ofs.write(reinterpret_cast<char*>(&course_number), sizeof (unsigned long));
     return ofs;
}



ifstream & operator>> (ifstream& ifs, Degree& _degree)
{
    unsigned long length;
    ifs.read(reinterpret_cast<char*>(&(length)), sizeof (unsigned long));
    char * name=new char[length];
    ifs.read(name,  static_cast<long>(length * sizeof (char)));
    _degree.name=name;
    //char * id=new char [8];
    ifs.read(_degree.id, 4 * sizeof (char));
    //delete [] id;
    unsigned long student_number;
    unsigned long course_number;
    ifs.read(reinterpret_cast<char*>(&student_number), sizeof (unsigned long));
    ifs.read(reinterpret_cast<char*>(&course_number), sizeof (unsigned long));
    if (student_number>0){
        _degree.stulist.reserve(student_number);
    }
    if (course_number>0){
        _degree.courselist.reserve(course_number);
    }

    delete [] name;
    return ifs;
}
