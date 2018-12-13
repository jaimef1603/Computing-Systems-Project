#include "Seminar.h"
#include <iostream>
#include "Link_prof_res.h"
#include <limits>
#include "Utilities.h"
#include <sstream>
#include "VirtualCampus.h"

Seminar::Seminar(VirtualCampus *vc, string n, string id, unsigned seatsValue, Professor *coord,  Date when, Professor *spe)
    :Resource(id, n)
{
    mycampus=vc;
    maxseats=seatsValue;
    eventDate=when;

    teachers[0]=teachers[1]=nullptr;

    if (coord)
        coord->enroll(this, role::coordinator);

    if (spe)
        spe->enroll(this, role::speaker);
}



Seminar::~Seminar()
{
    for (int i = int(students.size()-1) ; i>=0; i--){
        if (students[unsigned(i)]){
            delete students[unsigned(i)];
        }
    }

    for (unsigned i =0; i<2; i++){
        if (teachers[i]){
            delete teachers[i];
        }
    }
}



unsigned Seminar::getmaxseats()const
{
    return maxseats;
}



void Seminar::setmaxseats(unsigned s)
{
    maxseats=s;
}



Date Seminar::getdate()const
{
    return eventDate;
}



void Seminar::setdate(Date when)
{
    eventDate=when;
}




Link_prof_res* Seminar::getspeaker()const
{

    return teachers[0];
}



Link_prof_res* Seminar::getcoordinator()const
{
    return teachers[1];
}



void Seminar::addteacher(Link_prof_res *newteacher)
{
    if (newteacher->getRole()==role::coordinator){

        if(teachers[0]!=nullptr)
            delete teachers[0];

        teachers[0]=newteacher;
        return;
    }
    if (newteacher->getRole()==role::speaker){

        if(teachers[1]!=nullptr)
            delete teachers[1];

        teachers[1]=newteacher;
        return;

    }
}



void Seminar::showDetails()    //Function to show seminar details
{
    cout<<"Name: "<<this->name<<endl<<"ID: "<<this->identification<<endl;
    cout<<"Number of seats: "<<this->maxseats<<" Occupied: "<<this->students.size()<<endl
       <<"Date: "<<eventDate<<endl;
    for (unsigned i=0; i<2; i++){
        if (teachers[i]){
            cout<<teachers[i]->getRoleName()<<": "<<teachers[i]->getteacher()->getname()<<endl;
        }
    }
}



void Seminar::options()    //Function which contains the option menu of seminar
{
   //Set coordinator, set speaker, add student, remove student, edit

    vector <Menu<Seminar>::Menu_option> options;

    options.push_back(Menu<Seminar>::Menu_option(1, &Seminar::options_coordinator, "Set the coordinator", this));
    options.push_back(Menu<Seminar>::Menu_option(2, &Seminar::options_speaker, "Set the speaker", this));
    options.push_back(Menu<Seminar>::Menu_option(3, &Seminar::options_addstudent, "Add a student", this));
    options.push_back(Menu<Seminar>::Menu_option(4, &Seminar::options_removestudent, "Remove a student", this));
    options.push_back(Menu<Seminar>::Menu_option(5, &Seminar::edit, "Edit", this));
    Menu<Seminar> Seminar_Options_menu (options, "Options of seminar: ", &Seminar::showDetails, this);
    Seminar_Options_menu.run();

}



void Seminar::options_coordinator()   //Function to choose the coordinator of a seminar
{

    Menu<Professor> professorSelector(mycampus->getTeachers(), Professor::gimmethename(), "Choose a teacher to set the coordinator");
    Professor *temp= professorSelector.run_selector();
    if (temp)
        temp->enroll(this, role::coordinator);
}



void Seminar::options_speaker()   //Function to choose the speaker of a seminar
{

    Menu<Professor> professorSelector(mycampus->getTeachers(), Professor::gimmethename(), "Choose a teacher to set the speaker");
    Professor *temp= professorSelector.run_selector();
    if (temp)
        temp->enroll(this, role::speaker);
}



void Seminar::options_addstudent()    //Function to add a student to a seminar
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



void Seminar::options_removestudent()     //Function to remove a student from a seminar
{
    Link_stu_res* selected_student;
    vector<Menu<Link_stu_res>::Menu_option> selector_options;



     for (unsigned i=0; i<students.size(); i++){
         selector_options.push_back(Menu<Link_stu_res>::Menu_option(i+1, nullptr, to_string(students[i]->getStudent().getSIN()), students[i]));
     }
     Menu<Link_stu_res> studentSelector (selector_options, "Select the student you want to remove");
        selected_student = studentSelector.run_selector();
        if (selected_student)
            delete selected_student;

}



void Seminar::edit()    //Function which contains the seminar's edit menu
{

    vector<Menu<Seminar>::Menu_option> options;

    options.push_back(Menu<Seminar>::Menu_option(1, &Resource::editName, "Edit Name", this));
    options.push_back(Menu<Seminar>::Menu_option(2, &Seminar::editID, "Edit Identification", this));
    options.push_back(Menu<Seminar>::Menu_option(3, &Seminar::editDate, "Edit Date", this));
    options.push_back(Menu<Seminar>::Menu_option(4, &Seminar::editMaxseats, "Edit maximum number of seats", this));

    Menu<Seminar> editMenu (options, "SEMINAR: "+ this->name+" - edit", &Seminar::showDetails, this);
    editMenu.run();

}


void Seminar::coordinatorcanediteverythingbuttheid()    //Function which contains the seminar's edit menu
{

    vector<Menu<Seminar>::Menu_option> options;

    options.push_back(Menu<Seminar>::Menu_option(1, &Resource::editName, "Edit Name", this));
    options.push_back(Menu<Seminar>::Menu_option(2, &Seminar::editDate, "Edit Date", this));
    options.push_back(Menu<Seminar>::Menu_option(3, &Seminar::editMaxseats, "Edit maximum number of seats", this));

    Menu<Seminar> editMenu (options, "SEMINAR: "+ this->name+" - edit", &Seminar::showDetails, this);
    editMenu.run();

}


void Seminar::editID()     //Function to edit the identification of a seminar
{
    std::string buffer;
    do {
       system("clear");
       cin.clear();
       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
       std::cout<<"Enter the new identification (CCCIIII, C=Letter, I=Number) or \'q\' to cancel: \nSEM";

    }while(!(std::cin>>std::ws>>buffer) || !checkResId("SEM"+buffer));

    if (buffer!="q"){
        identification="SEM"+buffer;
    }
}



void Seminar::editDate()    //Function to edit the date of a seminar
{
    unsigned day, month, year;
    std::string buffer;
    do {
       system("clear");
       cin.clear();
       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
       std::cout<<"Enter the new date (day month year) or \'q\' to cancel:";
       getline(std::cin, buffer, '\n');

               if (buffer=="q"){
                  return;
               }

    }while(!(istringstream(buffer)>>day>>month>>year));

    this->eventDate=Date(day, year, month);

}



void Seminar::editMaxseats()    //Function to edit the maximum number of seats of a seminar
{

    unsigned newValue;
    std::string buffer;
    do {
       system("clear");
       cin.clear();
       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
       std::cout<<"Enter the new value for the maximum number of seats or \'q\' to cancel:";
       std::cin>>std::ws>>buffer;

               if (buffer=="q"){
                  return;
               }

    }while(!(istringstream(buffer)>>newValue)  && newValue>students.size());

    this->maxseats=newValue;
}



void Seminar::addstudent(Link_stu_res *newstudent)
{
    bool flag = false;
    if (students.size()<maxseats){
        students.pushFront(newstudent);
        flag = true;
    }
    if (!flag){
        cerr<<"Seminar::addstudent(Link_us_res*); Student was not added.\n";
    }
}



void Seminar::removestudent(Link_stu_res *link)
{
    students.remove(link);
}



void Seminar::removeprofessor(Link_prof_res *link)
{
    int i;
    bool flag = false;
    for (i=0; i<2; i++){
        if (teachers[i]==link){
            teachers[i]=nullptr;
            flag = true;
        }
    }
        if (!flag){
            cerr<<"Seminar::removeprofessor(Link_prof_res*); No teacher removed.\n";
        }

}





// ---------------------FUNCTIONS FOR FILE HANDLING-----------------

ofstream & operator<< (ofstream& ofs, Seminar& _seminar)
{

    ofs << &_seminar;
    ofs.write(reinterpret_cast<char*>(&_seminar.eventDate), sizeof (Mark));
    ofs.write(reinterpret_cast<char*>(&_seminar.maxseats), sizeof(unsigned));
    unsigned long student_number = _seminar.students.size();
    ofs.write(reinterpret_cast<char*>(&student_number), sizeof (unsigned long));



    for(unsigned i=0; i<2; i++){
        if (_seminar.teachers[i]){
            const char * teacher_id = _seminar.teachers[i]->getteacher()->getidentifier().c_str();
            ofs.write(teacher_id, 8*sizeof(char));
        }else{
            ofs.write("\0\0\0\0\0\0\0\0", 8*sizeof(char));
        }
    }



    return ofs;
}



ifstream& operator>>(ifstream& ifs, Seminar& _seminar)
{
    ifs>>&_seminar;
    ifs.read(reinterpret_cast<char*>(&_seminar.eventDate), sizeof(Mark));
    ifs.read(reinterpret_cast<char*>(&_seminar.maxseats), sizeof(unsigned));
    unsigned long student_number;
    ifs.read(reinterpret_cast<char*>(&student_number), sizeof (unsigned long));
    _seminar.students.reserve(student_number);


    string id;
    char id_buffer [8];

    for(unsigned i=0; i<2; i++){
        strcpy(id_buffer, "");
        ifs.read(id_buffer, 8*sizeof(char));
        id = id_buffer;
        if (id.length()==7){
            int index = _seminar.mycampus->findTeacher(id);
            if (index !=-1){
                _seminar.mycampus->getTeachers()[unsigned(index)]->enroll(&_seminar, role(i));
            }
        }
    }




    return ifs;
}


