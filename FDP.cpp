#include "FDP.h"
#include <iostream>
#include "Link_stu_res.h"
#include "Link_prof_res.h"
#include <limits>
#include "Utilities.h"
#include "VirtualCampus.h"

FDP::FDP(string n, string id, VirtualCampus *vc,  Student *stu, Professor *tu, Professor *co_tu)
    :Resource(id, n)
{
    mycampus = vc;

    if (stu)
        stu->enroll(this);

    if (tu)
        tu->enroll(this, role::tutor);

    if (co_tu)
        co_tu->enroll(this, role::cotutor);

}



FDP::FDP(const FDP &other)
    :Resource(other.identification, other.name)
{
    teachers[0]=other.teachers[0];
    teachers[1]=other.teachers[1];
    student=other.student;

}



FDP& FDP::operator= (const FDP &other)
{
    this->Resource::operator=(other);
    teachers[0]=other.teachers[0];
    teachers[1]=other.teachers[1];
    student=other.student;

    return *this;
}



Link_prof_res* FDP::gettutor()const
{
    for (int i=0; i<2; i++){
        if (teachers[i]->getRole()==role::tutor){
            return teachers[i];
        }

    }
    return nullptr;
}



//void FDP::settutor(Professor* t)
//{
//    Link_prof_res *newlink= new Link_prof_res(t, this, role::tutor);
//    if (newlink!=nullptr && !newlink->checkHealth()){
//        teachers[0]=newlink;
//        newlink->connectProftoFDP();
//        newlink->connectResource();
//    }else{
//        std::cerr<<"FDP::settutor(Link_prof_res*); incomplete or null link passed, tutor will not be modified.\n";
//    }
//}



Link_prof_res* FDP::getco_tutor()const
{
    for (int i=0; i<2; i++){
        if (teachers[i]->getRole()==role::cotutor){
            return teachers[i];
        }

    }
    return nullptr;
}



//void FDP::setco_tutor(Professor* c_t)
//{
//    Link_prof_res *newlink= new Link_prof_res(c_t, this, role::cotutor);
//    if (newlink!=nullptr && !newlink->checkHealth()){
//        teachers[1]=newlink;
//    }else{
//        std::cerr<<"FDP::setco_tutor(Link_prof_res*); incomplete or null link passed, co_tutor will not be modified.\n";
//    }
//}



void FDP::editID()
{
    std::string buffer;
    do {
       system("clear");
       cin.clear();
       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
       std::cout<<"Enter the new identification (CCCIIII, C=Letter, I=Number) or \'q\' to cancel: \nFDP";

    }while(!(std::cin>>std::ws>>buffer) || !checkResId("FDP"+buffer));

    if (buffer!="q"){
        identification="FDP"+buffer;
    }
}



Link_stu_res* FDP::getstudent()const
{
    return student;
}



void FDP::setstudent(Student* stu)
{

    if (stu)
        stu->enroll(this);

//    Link_stu_res *newlink = new Link_stu_res(stu, this);
//    if (newlink!=nullptr && !newlink->checkHealth()){
//        student=newlink;
//    }else{
//        std::cerr<<"FDP::setstudent(Link_stu_res*); incomplete or null link passed, student will not be modified.\n";
//    }
}



void FDP::addteacher(Link_prof_res *newteacher)
{
    if (newteacher->getRole()==role::tutor){
        if(teachers[0]!=nullptr){

            delete (teachers[0]);
            teachers[0]=newteacher;
            return;

        }else{
            teachers[0]=newteacher;
            return;
        }
    }
    if (newteacher->getRole()==role::cotutor){
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



void FDP::addstudent(Link_stu_res *newstudent)
{
    student=newstudent;
}



void FDP::removestudent(Link_stu_res *link)
{
    if (student==link && student != nullptr){
        student=nullptr;
    }else{
        cerr<<"FDP::removestudent(Link_stu_res *); Link passed does not correspond to this FDP or there isn´t a student asigned.\n";
    }
}



void FDP::removeprofessor(Link_prof_res* link)
{
    int i;
    bool flag = false;
    for (i=0; i<2; i++){
        if (teachers[i]==link){
            flag = true;
            for(;i<2; i++){
                if (i!=1){
                    teachers[i]=teachers[i+1];
                }else{
                    teachers[i]=nullptr;
                }
            }
            break;
        }

        if (!flag){
            cerr<<"FDP::removeprofessor(Link_prof_res*); No teacher removed.\n";
        }
    }
}



void FDP::options()
{
    vector <Menu<FDP>::Menu_option> options;

    options.push_back(Menu<FDP>::Menu_option(1, &FDP::options_settttutor, "Set the tutor", this));
    options.push_back(Menu<FDP>::Menu_option(2, &FDP::options_ssseeeetCo_tuttor, "Set the co-tutor", this));
    options.push_back(Menu<FDP>::Menu_option(3, &FDP::options_setstudent, "Add a student", this));
    options.push_back(Menu<FDP>::Menu_option(4, &FDP::options_removeStudent, "Remove the current student", this));
    options.push_back(Menu<FDP>::Menu_option(5, &FDP::edit, "Edit", this));
    Menu<FDP> FDP_Options_menu (options, 'q', "Options of FDP: ", &FDP::showDetails, this);
    FDP_Options_menu.run();

}



void FDP::options_settttutor()
{
    Menu<Professor> professorSelector(mycampus->getTeachers(), Professor::gimmethename(), "Choose a teacher to set the tutor");
    Professor *temp= professorSelector.run_selector();
    if (temp){
        temp->enroll(this, role::tutor);
    }
}


void FDP::options_ssseeeetCo_tuttor()
{
    Menu<Professor> professorSelector(mycampus->getTeachers(), Professor::gimmethename(), "Choose a teacher to set the co-tutor");
    Professor *temp= professorSelector.run_selector();
    if (temp)
        temp->enroll(this, role::cotutor);
}



void FDP::options_setstudent()
{
    Degree *selected_degree;
    Student *selected_student;
    Menu<Degree> degreeSelector(mycampus->getDegrees(), Degree::gimme_the_name(), "Select the degree that the student belongs to");

    selected_degree = degreeSelector.run_selector();
    if (selected_degree){
        Menu<Student> studentSelector(selected_degree->getStudents(), Student::gimmethename(), "Select the student");
        selected_student = studentSelector.run_selector();
        if (selected_student)
            selected_student->enroll(this);
    }
}



void FDP::options_removeStudent()
{
    char sel;

    do {
        system("clear");
        if (!cin.good()){
                cin.ignore(std::numeric_limits<int>::max(), '\n');
    }

        cout<< "Are you sure you want to remove the current student? (y/n)\n";

    }while (!(cin>>ws>>sel) || (sel != 'y' && sel != 'Y' && sel!='n' && sel != 'N'));

    if (sel=='Y' || sel == 'y')
    {
        delete student;
    }

}



void FDP::edit()
{
    vector<Menu<FDP>::Menu_option> options;

    options.push_back(Menu<FDP>::Menu_option(1, &Resource::editName, "Edit Name", this));
    options.push_back(Menu<FDP>::Menu_option(2, &FDP::editID, "Edit Identification", this));
    Menu<FDP> editMenu (options, 'q', "FINAL DEGREE PROJECT: "+ this->name+" - edit");
    editMenu.run();
}



void FDP::showDetails()
{
  cout<<"ID: "<<this->identification<<endl;
  cout<<"Title: "<<this->name<<endl;
  cout<<"Author: "<<this->student->getStudent().getname();
  for (unsigned i=0; i<2; i++){
      if (teachers[i]){
          cout<<teachers[i]->getRoleName()<<": "<<teachers[i]->getteacher()->getname()<<endl;
      }
  }

}
