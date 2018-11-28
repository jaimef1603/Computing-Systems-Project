#include "Course.h"
#include "Utilities.h"
#include "Degree.h"
#include "Student.h"
#include "VirtualCampus.h"

Course::Course(string id, Degree *d, int c, string s, Link_prof_res **t)
    :Resource(id, s)
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
    :Resource(c.identification, c.status)
{
    if (c.identification.c_str()==nullptr || c.status.c_str()==nullptr || c.degree==nullptr){
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
    if (c.identification.c_str()==nullptr || c.status.c_str()==nullptr || c.degree==nullptr){
        std::cerr<<"Course:operator=(const Course&); (Warning) Some atribute of original object is invalid, *this will not be modified.\n";
    }else{
        identification=c.identification;
        status=c.status;
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



void Course::edit()
{
    int selection;
    do{
        //do{
        system("clear");
        cout<<"1: Edit ID 2:Edit credits 3: Back\n";
        cin>>selection;
        // }while(selection !=1 && selection != 2);
        switch (selection) {
        case 1:{
            string newname;
            bool valid=false;
            do {
                system("clear");
                cout<<"Enter the new ID CCCIIII (C=char, I=number) or a single char to exit\n"<<endl;
                cin>>ws>>newname;
                if (newname.length()==1){
                    break;
                }
                if (!(valid=checkResId(newname))){
                    cout<<"Enter a valid ID CCCIIII (C=char, I=number)\n"<<endl;
                }
            }while (!valid);
            if (valid){
                this->setIdentification(newname);
            }
            break;
        }
        case 2:
        {
            int newc;
            cout<<"Enter the new value for credits.\n"<<endl;
            cin>>newc;
            setcredits(newc);
        }break;
        case 3: return;
        default:
            cout<<"Enter a valid number(1-3).\n\tPress any key to retry."<<endl;
            getchar();
            break;
        }
    }while(true);
}



void Course::options()
{
    int selection;
    cout<<"1: Add Student \n2: Remove student \n3: Back\n";
    do {
        cin>>selection;
        if (selection <1 || selection >3){
            system("clear");
            cout<<"1: Add Student \n2: Remove student \n3: Back\n";
            cout<<"Select a valid number (1-3) or -1 to exit"<<endl;
        }
    }while((selection <1 && selection !=-1) || selection >3);

    switch (selection) {
    case 1:{
        string identification;
        int index=-1;
        do{
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
            degree->getStudents()[index].enroll(this);
        }
        break;
    }
    case 2: {
        int selection =-1;
        do {
            for (int i=0; i<studentlist.getsize(); i++){
                cout<<i+1<<": "<<studentlist[i]->getStudent().getidentifier()<<endl;
            }
            cout << "Select the student you want to remove (1-"<<studentlist.getsize()<<") or -1 to cancel: ";
            cin>>selection;
        }while((selection<1 && selection !=-1)||selection>studentlist.getsize());
        if (selection!=-1){
            delete studentlist[selection-1];
        }

    }
        break;
    case 3: return;
    }
    return;
}



void Course::showdetails()
{
    cout<<"ID: "<<identification<<endl;
    cout<<"Credits: "<<credits<<endl;
    cout<<"Teachers: "<<endl;
    for (int i=0; i<2; i++){
        if(teachers[i]!=nullptr){
            cout<<"\t"<<teachers[i]->getteacher()->getidentifier()<<": "<<teachers[i]->getRoleName()<<endl;
        }
    }
    cout<<"Number of students: "<<studentlist.getsize()<<endl;

}



void Course::addteacher(Link_prof_res *newteacher)
{

    if (newteacher->getRole()==role::named_chair){
        if(teachers[0]!=nullptr){

                delete teachers[0];
                teachers[0]=newteacher;
                return;

        }else{
            teachers[0]=newteacher;
            return;
        }
    }else{
        if(teachers[1]!=nullptr){

                delete teachers[1];
                teachers[1]=newteacher;
                return;

        }else{
            teachers[1]=newteacher;
            return;
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
