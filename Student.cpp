﻿#include <iostream>
#include <string>
#include <sstream>
#include "VirtualCampus.h"
#include "Menu.h"


using namespace std;

unsigned Student::count;

Student::Student()
    :User(),mycourses(), myseminars()
{
    SIN=1000000 + count;
    mydegree=nullptr;
    myfdp=nullptr;
    count+=1;
}



Student::Student(Degree *d, string n)
    :User(), mycourses(), myseminars()
{
    setname(n);
    SIN=1000000 + count;
    mydegree=d;
    myfdp=nullptr;
    count+=1;
}



Student::Student (const Student &s)
    :mycourses(s.mycourses), myseminars(s.myseminars)
{
    SIN=s.SIN;
    mydegree=s.mydegree;
    myfdp=s.myfdp;
}



Student::~Student()
{
    for (int i = int(mycourses.size())-1; i>=0; i-- ){
        delete mycourses[unsigned(i)];
    }
    for (int i = int(myseminars.size())-1; i>=0; i--){
        delete myseminars[unsigned(i)];
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



ostream& operator<<(ostream& os, const Student& stu)
{
    os<<stu.SIN<<endl;
    return os;
}



void Student::setCount(unsigned c)
{
    count = c;
}



unsigned Student::getCount()
{
    return count;
}



unsigned Student::getSIN(){
    return SIN;
}



void Student::setSIN(unsigned s)
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
}



/* _______________________________________
  |                                       |
  |---------- COURSE FUNCTIONS -----------|
  |_______________________________________|
*/


void Student::my_courses()
{

    vector<Menu<Student>::Menu_option> options;
    options.reserve(3);
    options.emplace_back(1, &Student::course_view, "View Course", this);
    options.emplace_back(2, &Student::course_enrolling_func, "Enroll to a course", this);
    options.emplace_back(3, &Student::course_droppin_func, "Drop a currently coursing course", this);

    Menu<Student> menu(options, "---YOUR COURSES---", &Student::showCourses, this);

    menu.run();
}



void Student::course_view()
{

    unsigned i=1;


    vector<Menu<Link_stu_res>::Menu_option> options;
    options.reserve(mycourses.size());
    for (auto it:mycourses){
        options.emplace_back(i, &Link_stu_res::showDetails ,it->getResource()->getname(), *it);
        i++;
    }

    Menu<Link_stu_res> menu(options, "Select the course you want to see\nYOUR COURSES:");
    menu.set_settings({'q', menu_config::vertical, 0, "Enter a valid option", '[', ']', true});
    menu.run();
}



void Student::course_enrolling_func()
{

    Course * to_enroll = nullptr; //Pointer to the course that this will be enrolled in. Will be assigned by the selector
    string option_name;
    unsigned i =1;
    vector<Menu<Course>::Menu_option> options;
    options.reserve(mydegree->getCourses().size());
    for (auto it:mydegree->getCourses()){
        option_name = it->getname()+" ID: "+it->getIdentification();
        options.emplace_back(i, nullptr, option_name, (*it));
        i++;
    }

    Menu<Course> menu(options, ("---COURSES OF "+mydegree->getname()+"---"));

    to_enroll = menu.run_selector();   //Assigning the course to the pointer,
    if (to_enroll){                    // if the selector returns nullptr it means
        //the user aborted the operation so we don't enroll
        for (auto it: mycourses){
            if (it->getResource() == to_enroll){    //We check if the student is already enrolled in this course.
                cout<<"You are already enrolled in this course"<<endl;
                cin.ignore(numeric_limits<int>::max(), '\n');
                cin.get();
                return;
            }
        }
        enroll(to_enroll);
    }

}



void Student::course_droppin_func()
{
    Link_stu_res *to_drop;
    Course *Course_to_drop;
    string option_name;
    unsigned i=1;

    vector<Menu<Link_stu_res>::Menu_option> options;

    options.reserve(mycourses.size());
    for (auto it:mycourses){
        option_name = it->getResource()->getname()+" ID: "+it->getResource()->getIdentification();
        options.emplace_back(i, nullptr, option_name, (*it));
        i++;
    }

    Menu<Link_stu_res> menu(options, "---YOUR COURSES---");

    to_drop=menu.run_selector();
    if(to_drop != nullptr){
        Course_to_drop = dynamic_cast<Course*>(to_drop->getResource());
        Drop(Course_to_drop);
    }

}



void Student::Drop(Course *c)
{
    Link_stu_res link (this, c);
    for (unsigned i=0; i<mycourses.size(); i++){
        if (*mycourses[i]==link){
            delete mycourses[i];
        }
    }
}



void Student::addCourse(Link_stu_res *link)
{
    mycourses.pushFront(link);
}



void Student::enroll(Course *cour)
{

    Link_stu_res *newLink = new Link_stu_res(this, cour);

    newLink->connectStutoCourse();
    newLink->connectResource();

}


void Student::showCourses()
{
    unsigned i=1;
    for (auto it: mycourses){
        cout<<" "<<i<<": "
           <<it->getResource()->getname()
          <<" ID: "<<it->getResource()->getIdentification()
         <<endl;
        i++;
    }
}



/* _______________________________________
  |                                       |
  |---------- SEMINAR FUNCTIONS-----------|
  |_______________________________________|
*/



void Student::my_seminars()
{
    vector<Menu<Student>::Menu_option> options;
    options.reserve(3);
    options.emplace_back(1, &Student::seminar_view, "View a Seminar", this);
    options.emplace_back(2, &Student::seminar_enrolling_func, "Enroll to a seminar", this);
    options.emplace_back(3, &Student::seminar_droppin_func, "Drop a seminar", this);

    Menu<Student> menu(options, "---YOUR SEMINARS---", &Student::showSeminars, this);

    menu.run();
}



void Student::seminar_view()
{
    Menu<Link_stu_res> menu(myseminars, &Link_stu_res::showDetails, "Select the seminar you want to see\nYOUR SEMINARS:");
    menu.set_settings({'q', menu_config::vertical, 0, "Enter a valid option", '[', ']', true});
    menu.run();
}



void Student::seminar_enrolling_func()
{
    Seminar * to_enroll = nullptr; //Pointer to the seminar that this will be enrolled in. Will be assigned by the selector
    string option_name;
    unsigned i =1;
    vector<Menu<Seminar>::Menu_option> options;
    options.reserve(mydegree->getVc().getSeminars().size());
    for (auto it:mydegree->getVc().getSeminars()){
        option_name = it->getname()+" ID: "+it->getIdentification();
        options.emplace_back(i, nullptr, option_name, (*it));
        i++;
    }

    Menu<Seminar> menu(options, ("---SEMINARS AVAILABLE---"));

    to_enroll = menu.run_selector();   //Assigning the seminar to the pointer,
    if (to_enroll){                    // if the selector returns nullptr it means
        //the user aborted the operation so we don't enroll
        for (auto it: myseminars){
            if (it->getResource() == to_enroll){    //We check if the student is already enrolled in this seminar.
                cout<<"You are already enrolled in this seminar"<<endl;
                cin.ignore(numeric_limits<int>::max(), '\n');
                cin.get();
                return;
            }
        }
        enroll(to_enroll);
    }

}



void Student::seminar_droppin_func()
{

    Link_stu_res *to_drop;
    Seminar *Seminar_to_drop;
    string option_name;
    unsigned i=1;

    vector<Menu<Link_stu_res>::Menu_option> options;

    options.reserve(myseminars.size());
    for (auto it:myseminars){
        option_name = it->getResource()->getname()+" ID: "+it->getResource()->getIdentification();
        options.emplace_back(i, nullptr, option_name, (*it));
        i++;
    }

    Menu<Link_stu_res> menu(options, "---YOUR SEMINARS---");

    to_drop=menu.run_selector();
    if(to_drop != nullptr){
        Seminar_to_drop = dynamic_cast<Seminar*>(to_drop->getResource());
        Drop(Seminar_to_drop);
    }

}



void Student::showSeminars()
{
    unsigned i=1;
    for (auto it: myseminars){
        cout<<" "<<i<<": "
           <<it->getResource()->getname()
          <<" ID: "<<it->getResource()->getIdentification()
         <<endl;
        i++;
    }
}



void Student::Drop(Seminar *s)
{
    Link_stu_res link (this, s);
    for (unsigned i=0; i<myseminars.size(); i++){
        if (*myseminars[i]==link){
            delete myseminars[i];
        }
    }
}



void Student::addSeminar(Link_stu_res *link)
{
    myseminars.pushFront(link);
}



void Student::enroll(Seminar *setminar)
{
    Link_stu_res *newLink = new Link_stu_res(this, setminar);

    newLink->connectStutoSeminar();
    newLink->connectResource();
}



/* _______________________________________
  |                                       |
  |------------ FDP FUNCTIONS ------------|
  |_______________________________________|
*/



void Student::my_fdps()
{
    vector<Menu<Student>::Menu_option> options;
    options.reserve(3);
    options.emplace_back(1, &Student::fdp_view, "View my fdp", this);
    options.emplace_back(2, &Student::fdp_enrolling_func, "Enroll to currently existing fdp", this);
    options.emplace_back(3, &Student::fdp_droppin_func, "Drop my current fdp", this);

    Menu<Student> menu(options, "---YOUR FDP---", &Student::showFDP, this);

    menu.run();
}



void Student::fdp_view()
{
    if(myfdp){
        myfdp->showDetails();
    }else{
        cout<<"You currently don't have an FDP assigned"<<endl;
    }
    cin.ignore(numeric_limits<char>::max(), '\n');
    cin.get();
}



void Student::fdp_enrolling_func()
{

    FDP * to_enroll = nullptr; //Pointer to the seminar that this will be enrolled in. Will be assigned by the selector
    string option_name;
    unsigned i =1;

    if (!myfdp){                                    // If the student doesn't have an fdp.
        vector<Menu<FDP>::Menu_option> options;
        //options.reserve(mydegree->getVc().getFDPs().size());
        for (auto it:mydegree->getVc().getFDPs()){
            if (!(it->getstudent())){
                option_name = it->getname()+" ID: "+it->getIdentification();
                options.emplace_back(i, nullptr, option_name, (*it));
            }
            i++;
        }

        Menu<FDP> menu(options, ("---FDPs ASSIGNABLE---\n If you want to propose your own FDP contact an administrator"));

        to_enroll = menu.run_selector();   // Assigning the seminar to the pointer,
        if (to_enroll){                    // if the selector returns nullptr it means
            enroll(to_enroll);             // the user aborted the operation so we don't enroll
        }
    }else{
        cout<<"You are already have a Final Degree Project, drop from your current project before";
        cin.ignore(numeric_limits<int>::max(), '\n');
        cin.get();
    }

}



void Student::fdp_droppin_func()
{
    char answer;
    do{
        if (!cin.good()){
            cin.clear();
            cin.ignore(numeric_limits<char>::max(), '\n');
        }
        cout<<"Are you sure you want to leave your current PDP? (Y/N)\n this topic will be assignable again"<<endl;
        cin>>answer;
    }while( !cin.good() || (answer!='y' && answer!='Y' && answer!='n' && answer!='N' ));

        if (answer=='y' || answer=='Y'){
            delete myfdp;
        }

}



void Student::showFDP()
{
    if(myfdp){
        cout<<" Title: "
           <<myfdp->getResource()->getname()
          <<" ID: "<<myfdp->getResource()->getIdentification()
         <<endl;
    }
}


void Student::Dropfdp()
{
    if (myfdp!= nullptr){
        delete myfdp;
    }
}



void Student::addFDP(Link_stu_res *link)
{
    if(myfdp==nullptr){
        myfdp=link;
    }
}



void Student::enroll(FDP *project)
{
    Link_stu_res *newLink = new Link_stu_res(this, project);

    newLink->connectStutoFDP();
    newLink->connectResource();

}



void Student::showDetails()        //Function to show student's details
{
    cout<<"SIN: "<<getidentifier();
    cout<<"  Name: "<<name;
    cout<<"  Courses enrolled: "<<mycourses.size();
    cout<<"  Seminars enrolled: "<<myseminars.size();
    cout<<"  Has FDP: ";
    if(myfdp!=nullptr){
        cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
    }
}



void Student::menu(){

    vector<Menu<Student>::Menu_option> options;
    options.reserve(3);
    options.emplace_back(1, &Student::my_courses, "My Courses", this);
    options.emplace_back(2, &Student::my_seminars, "My Seminars", this);
    options.emplace_back(3, &Student::my_fdps, "My FDP", this);

    Menu<Student> menu(options, "---WELCOME TO YOUR MAIN MENU---", &Student::showDetails, this);

    menu.run();

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



ofstream & operator<< (ofstream& ofs, Student& _student)
{
    unsigned long fdpid_length=0;

    ofs << &_student;
    const char *id = _student.getidentifier().c_str();
    ofs.write(id,  8 * sizeof (char));
    unsigned long seminar_number = _student.myseminars.size();
    unsigned long course_number = _student.mycourses.size();
    ofs.write(reinterpret_cast<char*>(&seminar_number), sizeof(unsigned long));
    ofs.write(reinterpret_cast<char*>(&course_number), sizeof(unsigned long));

    if (_student.myfdp){
        fdpid_length = _student.myfdp->getResource()->getIdentification().length()+1;
        const char *fdpid = _student.myfdp->getResource()->getIdentification().c_str();
        ofs.write(reinterpret_cast<char*>(&fdpid_length), sizeof (unsigned long));
        ofs.write(fdpid, fdpid_length*sizeof (char));
    }else{
        ofs.write(reinterpret_cast<char*>(&fdpid_length), sizeof (unsigned long));

    }
    return ofs;
}



ifstream& operator>>(ifstream& ifs, Student& _student)
{
    unsigned long fdpid_length;

    ifs>>&_student;
    char id [8];
    ifs.read(id, 8 * sizeof (char));
     _student.SIN=unsigned(atoi(id));

     unsigned long seminar_number = _student.myseminars.size();
     unsigned long course_number = _student.mycourses.size();
     ifs.read(reinterpret_cast<char*>(&seminar_number), sizeof(unsigned long));
     ifs.read(reinterpret_cast<char*>(&course_number), sizeof(unsigned long));
     ifs.read(reinterpret_cast<char*>(&fdpid_length), sizeof(unsigned long));
    _student.myseminars.reserve(seminar_number);
    _student.mycourses.reserve(course_number);
    if(fdpid_length>0){
        char *fdpid=new char[fdpid_length];
        ifs.read(fdpid, unsigned(fdpid_length*sizeof (char)));
        int index = _student.mydegree->getVc().findFDP(fdpid);
        if (index!=-1){
            _student.enroll(_student.mydegree->getVc().getFDPs()[unsigned(index)]);
        }else{
            cerr<<"Student: "<<_student.getidentifier()<<"; FDP "<<fdpid<<" not found, missmatch in database\n";
        }
    }
    return ifs;
}
