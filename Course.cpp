#include "Course.h"
#include "Utilities.h"
#include "Degree.h"
#include "Student.h"
#include "VirtualCampus.h"
#include <sstream>
#include <limits>

Course::Course(string n, string id, Degree *d, int c, Link_prof_res **t)
    :Resource(id, n)
{
    degree=d;
    credits=c;
    if (t!=nullptr){ //we should check as well if the links link to teacher.
        for (int i=0; i<2; i++){
            teachers[i]=t[i];
        }
    }else{
        for (int i=0; i<2; i++){
            teachers[i]=nullptr;
        }
    }
}



Course::Course(const Course &c)
    :Resource(c.identification, c.name)
{
    if (c.identification.empty() || c.name.empty() || c.degree==nullptr){
        std::cerr<<"Course cpyconstructor: (Warning) some atribute of original object is invalid.\n";
    }
    degree=c.degree;
    credits=c.credits;
    studentlist=c.studentlist;
    for (int i=0; i<2; i++){
        if (c.teachers[i]!=nullptr){
            teachers[i]=c.teachers[i];
        }else{
            teachers[i]=nullptr;
        }
    }
}



Course& Course::operator= (const Course &c)
{
    if (c.identification.empty() || c.name.empty() || c.degree==nullptr){
        std::cerr<<"Course:operator=(const Course&); (Warning) Some atribute of original object is invalid, *this will not be modified.\n";
    }else{
        identification=c.identification;
        degree=c.degree;
        name=c.name;
        credits=c.credits;
        studentlist=c.studentlist;
        for (int i=0; i<2; i++){
            if (c.teachers[i]!=nullptr){
                teachers[i]=c.teachers[i];
            }else{
                teachers[i]=nullptr;
            }
        }
    }

    return *this;
}



int Course::getcredits()
{
    return credits;
}



void Course::setcredits(int c)
{
    credits=c;
}



void Course::edit()            //Edit Course attributes
{
    char selection;
    do{

        system("clear");
        cout<<"1: Edit name 2:Edit ID 3: Edit credits 4: Back\n";
        cin>>ws>>selection;
        switch (selection) {
        case '1':{
            editName();
            break;
        }
        case '2':{
            editID();
            break;
        }
        case '3':
        {
            string buffer;
            int newc;
            system("clear");
            cout<<"Enter the new value for credits.\n"<<endl;
            do{
                cin>>ws>>buffer;
                istringstream(buffer)>>newc;
                if (newc <=0){
                    system("clear");
                    cout<<"Enter a valid value for credits\n";
                }
            }while(newc<=0);
            setcredits(newc);
        }break;
        case '4': return;
        default:
            cout<<"Enter a valid number(1-4).\n\tPress any key to retry."<<endl;
            getchar();
            break;
        }
    }while(true);
}



void Course::editID()
{
    std::string buffer;
    do {
       system("clear");
       cin.clear();
       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
       std::cout<<"Enter the new identification (CCCIIII, C=Letter, I=Number) or \'q\' to cancel: \n"<<degree->getid();

    }while(!(std::cin>>std::ws>>buffer) || !checkResId(degree->getid()+buffer));

    if (buffer!="q"){
        identification=degree->getid()+buffer;
    }
}



void Course::options()      //Course's options
{
    char selection;
    do {
        system("clear");
        cout<<"Options of Course "<<this->getIdentification()<<":"<<endl;
        cout<<"1: Add Student \n2: Remove student \n3: Back\n";
        cin>>ws>>selection;
        switch (selection) {
        case '1':{
            string identification;
            int index=-1;
            do{
                system("clear");
                degree->showstudents();
                cout<<"Enter the identification of the student you want to add or \"cancel\" to exit: ";
                cin>>identification;
                if(identification=="cancel"){
                    break;
                }else{
                    index=degree->findStudent(identification);
                }
            }while(index==-1);
            if (index!=-1){
                degree->getStudents()[unsigned(index)]->enroll(this);
            }
            break;
        }
        case '2': {
            string buffer;
            int selection =-1;
            do {
                for (unsigned i=0; i<studentlist.size(); i++){
                    cout<<i+1<<": "<<studentlist[i]->getStudent().getidentifier()<<endl;
                }
                cout << "Select the student you want to remove (1-"<<studentlist.size()<<") or -1 to cancel: ";
                cin>>ws>>buffer;
                istringstream(buffer)>>selection;
            }while((selection<1 && selection !=-1)||selection>int(studentlist.size()));
            if (selection!=-1){
                delete studentlist[unsigned(selection)-1];
            }

        }
            break;
        case '3': return;
        default:
            cout<<"Select a valid number (1-3)"<<endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            break;
        }
    }while(true);
}



void Course::showdetails()        //Function to show course's details
{
    cout<<"ID: "<<identification<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Credits: "<<credits<<endl;
    cout<<"Teachers: "<<endl;
    for (int i=0; i<2; i++){
        if(teachers[i]!=nullptr){
            cout<<"\t"<<teachers[i]->getteacher()->getidentifier()<<": "<<teachers[i]->getRoleName()<<endl;
        }
    }
    cout<<"Number of students: "<<studentlist.size()<<endl;

}



void Course::addteacher(Link_prof_res *newteacher)
{

    if (newteacher->getRole()==role::named_chair){
        if(teachers[0]!=nullptr){
            if(teachers[1]==nullptr){
                teachers[1]=newteacher;
                return;
            }else if(teachers[1]->getRole()!=role::named_chair){
                delete teachers[1];
                teachers[1]=newteacher;
            }else{
                cout<<"No more space for new teachers in this course.\n";
            }

        }else{
            teachers[0]=newteacher;
            return;
        }
    if (newteacher->getRole()==role::associated){
        if(teachers[1]!=nullptr){
            if (teachers[1]->getRole()!=role::named_chair){
                delete teachers[1];
                teachers[1]=newteacher;
                return;
            }else{
                cout<<"All places in "<<this->getIdentification()<<" are ocupied by named chair professors.\n";
            }

        }else{
            teachers[1]=newteacher;
            return;
        }
    }

    }
}



void Course::addstudent(Link_stu_res *newstudent)
{
    studentlist.pushFront(newstudent);
}



void Course::removestudent(Link_stu_res *link){
    studentlist.remove(link);
}



void Course::removeprofessor(Link_prof_res *professor){
    for (int i=0; i<2; i++){
        if (teachers[i]==professor){
            for (; i<2; i++){
                if (i!=1){
                    teachers[i]=teachers[i+1];
                }else{
                    teachers[i]=nullptr;
                }
            }
        }
    }
}


//void Course::addUser(User *newUser){
//link_us_res *newLink= new(newUser, this)
//newLink->checkUserKind(newUser.getidentifier()); (returns if teacher or student)
//if teacher add to teachers[2] if there aren't two teachers yet;
//if student add to studentlist
//and add to courselist of student.
//studentlist.pushFront(newLink);
//newLink->connectCourseUser();

//}
