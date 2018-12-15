#include "Course.h"
#include "Utilities.h"
#include "Degree.h"
#include "Student.h"
#include "VirtualCampus.h"
#include <sstream>
#include <limits>

Course::Course(Degree *d, string n, string id, int c, Link_prof_res **t)
    :Resource(id, n)
{
    degree=d;
    credits=c;
    if (t!=nullptr){
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



Course::~Course()
{
    for (int i = int(studentlist.size()-1) ; i>=0; i--){
        if (studentlist[unsigned(i)]){
            delete studentlist[unsigned(i)];
        }
    }

    for (unsigned i =0; i<2; i++){
        if (teachers[i]){
            delete teachers[i];
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



vector<Link_stu_res*>& Course::getStudents()
{
    return studentlist;
}



void Course::edit()            //Function to edit Course attributes (name , id and credits)
{
    char selection;
    do{

        system("clear");
        cout<<"Edit Course:\n"<<endl;
        cout<<"\t[1] Edit name\n \t[2] Edit ID\n \t[3] Edit credits\n \t'q' Back\n";
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
            do{
                cout<<"Enter the new value for credits or \'q\' to cancel: "<<endl;
                cin>>ws>>buffer;
                if(buffer=="q"){
                    break;
                }
                istringstream(buffer)>>newc;
                if (newc <=0){
                    system("clear");
                    cout<<"Enter a valid value for credits\n";
                }
            }while(newc<=0);
            if(buffer!="q"){
                setcredits(newc);
            }
        }break;
        case 'q': return;
        default:
            cout<<"Enter a valid number(1-4).\n\tPress any key to retry."<<endl;
            getchar();
            break;
        }
    }while(true);
}



void Course::editID()     //Function to edit the id of a course
{
    std::string buffer;
    bool valid;
    do {
        do {
            system("clear");
            if (!cin.good()){
                cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout<<"Enter the new identification (CCCIIII, C=Letter, I=Number) or \'q\' to cancel: \n"<<degree->getid();

        }while(!(std::cin>>std::ws>>buffer) || (!checkResId(degree->getid()+buffer) && buffer !="q"));

        if (buffer!="q"){
            valid = true;
            for (auto it: this->degree->getCourses()){
                if (it->getIdentification()==degree->getid()+buffer){
                    valid = false;
                    cout<<"There is already a course with this identification, choose another"<<endl;
                    cin.ignore(numeric_limits<char>::max(), '\n');
                    cin.get();
                }

            }
        }else{
            return;
        }
    }while (!valid);

    identification=degree->getid()+buffer;
}



void Course::options()      //Course's options
{
    char selection;
    do {
        system("clear");
        cout<<"Options of Course "<<this->getIdentification()<<":"<<endl;
        cout<<"  Students:\n";
        for (auto _student : studentlist){
            cout<<"\t"<<_student->getStudent().getname()
               <<"\tID: "<<_student->getStudent().getidentifier()<<endl;
        }
        cout<<"\t[1] Add Student\n \t[2] Remove Student\n \t'q' Back\n";
        cin>>ws>>selection;
        switch (selection) {
        case '1':{
            string identification;
            Student *to_enroll=nullptr;
            bool valid=true;
            int index=-1;
            do{
                system("clear");
                degree->showstudents();
                cout<<"Enter the identification of the student you want to add or \'q\'  to cancel: ";
                cin>>identification;
                if(identification=="q"){
                    break;
                }else{
                    index=degree->findStudent(identification);     //index is the position where the student is in stulist
                }
            }while(index==-1);
            if (index!=-1){                                             //if index==-1 means that the student is not in stulist
                to_enroll=degree->getStudents()[unsigned(index)];
                for (auto _student : studentlist){

                    if(to_enroll->getSIN()==_student->getStudent().getSIN()){        //we check if the student is already in the students enrolled in the course
                        cout   <<"\tThe student with ID: "<<_student->getStudent().getidentifier()
                              <<" is already enrolled in this course"<<endl;
                        cin.ignore(numeric_limits<int>::max(), '\n');
                        cin.get();
                        valid = false;
                    }
                }
                if(valid)    //if the student is not enrolled, we enroll it
                    to_enroll->enroll(this);
            }
            break;
        }
        case '2': {
            string buffer;
            int selection =-1;
            do {
                system("clear");
                for (unsigned i=0; i<studentlist.size(); i++){
                    cout<<i+1<<": "<<studentlist[i]->getStudent().getidentifier()<<endl;
                }
                cout << "Select the student you want to remove (1-"<<studentlist.size()<<") or \'q\' to cancel: ";
                cin>>ws>>buffer;
                if(buffer=="q"){
                    break;
                }
                istringstream(buffer)>>selection;
            }while(selection>int(studentlist.size()));
            if (selection!='q'){
                delete studentlist[unsigned(selection)-1];
            }

        }
            break;
        case 'q': return;
        default:
            cout<<"Select a valid number (1-3)"<<endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            break;
        }
    }while(true);
}



void Course::showDetails()        //Function to show course's details
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
                    cout<<"All places in "<<this->getIdentification()<<" are occupied by named chair professors.\n";
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



void Course::grade()
{
    vector<Menu<Link_stu_res>::Menu_option> options;
    options.reserve(studentlist.size());
    unsigned i = 1;
    for (auto it:studentlist){
        string option_name = it->getStudent().getname()+" ID: "+it->getStudent().getidentifier();
        options.emplace_back(i, &Link_stu_res::grade, option_name, (*it));
        i++;
    }

    Menu<Link_stu_res> students(options, name+"- GRADES - \nSelect the student you want to grade");
    students.run();
}





// ---------------------FUNCTIONS FOR FILE HANDLING-----------------

ofstream & operator<< (ofstream& ofs, Course& _course)
{

    ofs << &_course;
    unsigned long student_number = _course.studentlist.size();
    ofs.write(reinterpret_cast<char*>(&student_number), sizeof (unsigned long));

    for(unsigned i=0; i<2; i++){
        if (_course.teachers[i]){
            const char * teacher_id = _course.teachers[i]->getteacher()->getidentifier().c_str();
            role teacher_role = _course.teachers[i]->getRole();
            ofs.write(teacher_id, 8*sizeof(char));
            ofs.write(reinterpret_cast<char*>(&teacher_role), sizeof (role));
        }else{
            ofs.write("\0\0\0\0\0\0\0\0", 8*sizeof(char));
        }
    }



    return ofs;
}



ifstream& operator>>(ifstream& ifs, Course& _course)
{
    ifs>>&_course;
    unsigned long student_number;
    ifs.read(reinterpret_cast<char*>(&student_number), sizeof (unsigned long));
    _course.studentlist.reserve(student_number);

    string id;
    char id_buffer [8];
    role role_buffer;
    for(unsigned i=0; i<2; i++){
        strcpy(id_buffer, "");
        ifs.read(id_buffer, 8*sizeof(char));
        id = id_buffer;
        if (id.length()==7){
            ifs.read(reinterpret_cast<char*>(&role_buffer), sizeof (role));
            int index = _course.degree->getVc().findTeacher(id);
            if (index !=-1){
                _course.degree->getVc().getTeachers()[unsigned(index)]->enroll(&_course, role_buffer);
            }else{
                cerr<<"Course: "+_course.identification+"; Teacher "+id+" Not found, missmatch in database\n";
            }
        }
    }


    return ifs;
}
