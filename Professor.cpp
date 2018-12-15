#include "Professor.h"
#include <string>
#include "Utilities.h"
#include "VirtualCampus.h"
#include "Menu.h"

Professor::Professor()
    : User(), identifier("0"), courselist(), fdplist(), seminarlist()
{
    mycampus=nullptr;
}



Professor::Professor(VirtualCampus *vc, string n, string ident )
    :User(), courselist(), fdplist(), seminarlist()
{
    setname(n);
    identifier=ident;
    mycampus=vc;
}



Professor::Professor(const Professor& other)
    :User()
{
    identifier=other.identifier;
    mycampus=other.mycampus;
    this->courselist=other.courselist;
    this->fdplist=other.fdplist;
    this->seminarlist=other.seminarlist;
}



string Professor::getidentifier()
{
    return identifier;
}



void Professor::setidentifier(string ident)
{
    identifier=ident;
}



/* _______________________________________
  |                                       |
  |---------RESOURCE FUNCTIONS------------|
  |_______________________________________|
*/



void Professor::removeResource(Link_prof_res *link)
{
    int flag = courselist.remove(link) + seminarlist.remove(link)+fdplist.remove(link);
    if(flag==0){
        cerr<<"Student::removeResource(Link_stu_res*); Nothing to remove.\n";
    }
}



/* _______________________________________
  |                                       |
  |---------- COURSE FUNCTIONS------------|
  |_______________________________________|
*/



void Professor::addCourse(Link_prof_res *link)
{
    this->courselist.pushBack(link);
}



void Professor::manageCourses()
{
    char selection;
    do{
        system("clear");
        cout<<"COURSES:\n";
        cout<<"\t[1] Add Course\n\t[2] Delete Course\n\t'q' Back\n";
        cin>>selection;

        switch (selection) {
        case '1':
            selectCourseAndAdd();
            break;
        case '2':{
            Link_prof_res * selected_course;


            vector<Menu<Link_prof_res>::Menu_option> delete_options;
            delete_options.reserve(courselist.size());
            unsigned i=1;
            for ( auto _course: courselist){
                delete_options.emplace_back(i, nullptr, _course->getResource()->getname()+"\tID: "+_course->getResource()->getIdentification(), _course);
            }

            Menu<Link_prof_res> delete_selector (delete_options, "Choose the course you want to remove: ");
            selected_course = delete_selector.run_selector();


            if (selected_course)
                delete selected_course;




//            int index;
//            do{
//                system("clear");
//                cout<<"Courses of "<<this->getidentifier()<<" :"<<endl;
//                for(unsigned i=0; i<courselist.size(); i++){
//                    cout<<courselist[i]->getResource()->getIdentification()<<endl;
//                }
//                cout<<"Enter the id of the course you want to remove or \'q\' to cancel\n";
//                cin>>index;

//                if(index=='q'){
//                    return;
//                }

//            }while (index>=int(courselist.size()));

//            if(index!='q'){
//                delete courselist[unsigned(index)];
//            }
        }
            break;
        case 'q': return;
        default:
            cout<<"Select a valid number (1-2) or \'q\' to cancel\n\tPress any key to retry."<<endl;
            getchar();
            break;
        }
    }while (true);
}



void Professor::selectCourseAndAdd()       //Function to add a course
{
    char roletobe;
    Degree* selected_degree = nullptr;
    Course* selected_course = nullptr;
    vector<Menu<Degree>::Menu_option> selector_options;
    selector_options.reserve(mycampus->getDegrees().size());
    unsigned i=1;
    for ( auto _degree: mycampus->getDegrees()){
        selector_options.emplace_back(i, nullptr, _degree->getname()+"\tID: "+_degree->getid(), _degree);
    }

    Menu<Degree> degree_selector (selector_options, "Select the Degree to choose a Course: ");
    selected_degree = degree_selector.run_selector();


    if (selected_degree){


        vector<Menu<Course>::Menu_option> courses_options;
        selector_options.reserve(selected_degree->getCourses().size());
        unsigned i=1;
        for ( auto _course: selected_degree->getCourses()){
            courses_options.emplace_back(i, nullptr, _course->getname()+"\tID: "+_course->getIdentification(), _course);
        }

        Menu<Course> course_selector (courses_options, "Select the Course:");
        selected_course = course_selector.run_selector();

    if (selected_course){

        for (auto _course: courselist){
            if (selected_course==_course->getResource()){
                cout<<"This professor is already enrolled in this course\n";
                cin.ignore(numeric_limits<int>::max(), '\n');
                cin.get();
                return;
            }
        }

        do {
            system("clear");
            cout<<"Select Role:\n";
            cout<<"\t[1] Named Chair\n\t[2] Associated\n\t'q' Back";
            cin>>roletobe;
            switch (roletobe) {
            case '1':
                enroll(selected_course, role::named_chair);
                return;
            case '2':
                enroll(selected_course, role::associated);
                return;
            case 'q': return;
            default:
                cout<<"Select a valid number or \'q\' to cancel\n\tPress any key to retry"<<endl;
                break;
            }

        }while(true);

    }
}

}


void Professor::my_courses()
{
    vector<Menu<Professor>::Menu_option> options;
    options.reserve(3);
    options.emplace_back(1, &Professor::course_view, " Select a course", this);
    options.emplace_back(2, &Professor::course_enrolling_func, " Enter a course", this);
    options.emplace_back(3, &Professor::course_droppin_func, " Leave a course", this);

    Menu<Professor> menu(options, "PROFFESOR "+name+" - Your courses", &Professor::showCourses, this);

    menu.set_settings({'q', menu_config::horizontal, 2, "Enter a valid option", '[', ']', false});
    menu.run();
}



void Professor::course_droppin_func()
{
    Link_prof_res *to_drop;
    Course *Course_to_drop;
    string option_name;
    unsigned i=1;

    vector<Menu<Link_prof_res>::Menu_option> options;

    options.reserve(courselist.size());
    for (auto it:courselist){
        option_name = it->getResource()->getname()+" ID: "+it->getResource()->getIdentification();
        options.emplace_back(i, nullptr, option_name, (*it));
        i++;
    }

    Menu<Link_prof_res> menu(options, "---YOUR COURSES---\n\tSelect the course you want to leave");

    to_drop=menu.run_selector();
    if(to_drop != nullptr){
        Course_to_drop = dynamic_cast<Course*>(to_drop->getResource());
        Drop(Course_to_drop);
    }
}



void Professor::course_enrolling_func()
{
    system("clear");
    cout<<"If you want to participate in a course you must contact an administrator\n";

    cin.ignore(numeric_limits<char>::max(), '\n');
    cin.get();


}



void Professor::course_view()
{
    string option_name;
    char willyougrade;
    Link_prof_res* selected_course = nullptr;
    vector<Menu<Link_prof_res>::Menu_option> course_selector_options;
    course_selector_options.reserve(courselist.size());
    unsigned i = 1;
    for (auto it: courselist){
        option_name = it->getResource()->getname()+" ID: "+it->getResource()->getIdentification();
        course_selector_options.emplace_back(i, nullptr, option_name.c_str(), (*it));
        i++;
    }
    string selector_name = "MY COURSES - Select the course you want to view";
    Menu<Link_prof_res> course_selector (course_selector_options, selector_name );
    selected_course = course_selector.run_selector();

    if (selected_course){
        do {
            system("clear");
            if (!cin.good()){
                cin.clear();
                cin.ignore(numeric_limits<char>::max(), '\n');
            }
            selected_course->getResource()->showDetails();
            cout<<"\t[1] Grade \"q\" exit "<<endl;
            cin>>ws>>willyougrade;
        }while(!cin.good() && willyougrade!='q' && willyougrade!='1');

        //!cin.good() ||

        if (willyougrade == 'q'){
            return;
        }else{
            dynamic_cast<Course*>(selected_course->getResource())->grade();
        }

    }
}



void Professor:: enroll(Course* c, role r)
{
    Link_prof_res *newlink= new Link_prof_res (this, c, r);
    newlink->connectProftoCourse();
    newlink->connectResource();
}



void Professor::Drop(Course* s)
{
    Link_prof_res link (this, s);
    for (unsigned i=0; i<courselist.size(); i++){
        if (*courselist[i]==link){
            delete courselist[i];
        }
    }
}



void Professor::showCourses()
{
    unsigned i=1;
    for (auto it: courselist){
        cout<<" "<<i<<": "
           <<it->getResource()->getname()
          <<" ID: "<<it->getResource()->getIdentification()
         <<endl;
        i++;
    }
}



/* _______________________________________
  |                                       |
  |----------SEMINAR FUNCTIONS------------|
  |_______________________________________|
*/



void Professor::addSeminar(Link_prof_res *link)
{
    this->seminarlist.pushBack(link);
}



void Professor::manageSeminars()
{
    char selection;
    do {
        cout<<"SEMINARS:\n";
        cout<<"\t[1] Add Seminar\n\t[2] Delete Seminar\n\t'q' Back\n";
        cin>>selection;

        switch (selection) {
        case '1':
        {
            char r;
            string identification;
            int valid=-1;
            do {
                system("clear");
                mycampus->showAllSeminars();
                cout<<"Enter the id of the seminar you want to add or \'q \' to cancel\n";
                cin>>identification;
                if (identification == "q"){
                    break;
                }
                valid=mycampus->findSeminar(identification);
            }while(valid==-1);
            if (valid!=-1){
                do {
                    system("clear");
                    cout<<"Select Role: \n\t[1] Speaker\n\t[2] Coordinator\n\t\'q \' Back";
                    cin>>r;
                    switch (r) {
                    case '1':
                        enroll(mycampus->getSeminars()[unsigned(valid)], role::speaker);
                        return;
                    case '2':
                        enroll(mycampus->getSeminars()[unsigned(valid)], role::coordinator);
                        return;
                    case 'q': return;
                    default:
                        cout<<"Select a valid number"<<endl;
                        break;
                    }

                }while(true);

            }
        }
            break;
        case '2':{
            int index;
            do{
                if (!cin.good()){
                    cin.clear();
                    cin.ignore(numeric_limits<char>::max(), '\n');
                }
                system("clear");
                cout<<"Seminars of "<<this->getidentifier()<<" :"<<endl;
                for(unsigned i=0; i<seminarlist.size(); i++){
                    cout<<i+1<<": "<<seminarlist[i]->getResource()->getIdentification()<<endl;
                }
                cout<<"Select the seminar you want to remove or \'q\' to cancel\n";
                cin>>index;

                if(index=='q'){
                    return;
                }

            }while (!cin.good() || (index !='q') || index>int(seminarlist.size()));

            if(index!=-'q'){
                delete seminarlist[unsigned(index-1)];

            }
        }
            break;
        case 'q': return;
        default:
            cout<<"Select a valid number (1-2) or \'q\' to cancel\n\tPress any key to retry."<<endl;
            getchar();
            break;
        }
    }while (true);
}



void Professor:: enroll(Seminar* s, role r)
{
    Link_prof_res *newlink= new Link_prof_res (this, s, r);
    newlink->connectProftoSeminar();
    newlink->connectResource();
}



void Professor::Drop(Seminar* s)
{
    Link_prof_res link (this, s);
    for (unsigned i=0; i<seminarlist.size(); i++){
        if (*seminarlist[i]==link){
            delete seminarlist[i];
        }
    }
}



void Professor::my_seminars()
{
    vector<Menu<Professor>::Menu_option> options;
    options.reserve(3);
    options.emplace_back(1, &Professor::seminar_view, "Select a seminar", this);
    options.emplace_back(2, &Professor::seminar_enrolling_func, "Enter a seminar", this);
    options.emplace_back(3, &Professor::seminar_droppin_func, "Leave a seminar", this);

    Menu<Professor> menu(options, "PROFFESOR "+name+" - Your seminars", &Professor::showSeminars, this);

    menu.set_settings({'q', menu_config::horizontal, 2, "Enter a valid option", '[', ']', false});
    menu.run();
}



void Professor::seminar_droppin_func()
{
    Link_prof_res *to_drop;
    Seminar *Course_to_drop;
    string option_name;
    unsigned i=1;

    vector<Menu<Link_prof_res>::Menu_option> options;

    options.reserve(seminarlist.size());
    for (auto it:seminarlist){
        option_name = it->getResource()->getname()+" ID: "+it->getResource()->getIdentification();
        options.emplace_back(i, nullptr, option_name, (*it));
        i++;
    }

    Menu<Link_prof_res> menu(options, "---YOUR COURSES---\n\tSelect the seminar you want to leave");

    to_drop=menu.run_selector();
    if(to_drop != nullptr){
        Course_to_drop = dynamic_cast<Seminar*>(to_drop->getResource());
        if (to_drop->getRole()!=role::coordinator){
            Drop(Course_to_drop);
        }else{
            cout<<"Selected: "<<to_drop->getResource()->getname()
               <<" ID: "<<to_drop->getResource()->getIdentification()
              <<"\nYou are currently the coordinator of this Seminar, thus you can not leave it."
                "\nIf you want to leave this seminar you must contact an administrator"<<endl;
            cin.ignore(numeric_limits<char>::max(), '\n');
            cin.get();
        }
    }
}



void Professor::seminar_enrolling_func()
{
    Seminar * to_enroll = nullptr; //Pointer to the seminar that this will be enrolled in. Will be assigned by the selector
    string option_name;
    unsigned i =1;
    vector<Menu<Seminar>::Menu_option> options;
    options.reserve(mycampus->getSeminars().size());
    for (auto it:mycampus->getSeminars()){
        option_name = it->getname()+" ID: "+it->getIdentification();
        options.emplace_back(i, nullptr, option_name, (*it));
        i++;
    }

    Menu<Seminar> menu(options, ("---SEMINARS AVAILABLE---"));
    char role_to_be;
    to_enroll = menu.run_selector();
    if (to_enroll){


        if (!to_enroll->getcoordinator()){
            if (to_enroll->getspeaker()){            //no coordinator but speaker
                do{
                    if (!cin.good()){
                        cin.clear();
                        cin.ignore(numeric_limits<char>::max(), '\n');
                    }
                    system("clear");
                    to_enroll->showDetails();
                    cout<<"\t[1]"<<" Join as coordinator\n";
                    cin>>ws>>role_to_be;
                }while(!cin.good() || (role_to_be!='1' && role_to_be!='q'));
                if (role_to_be=='q'){
                    return;
                }else{
                    enroll(to_enroll, role::coordinator);
                }

            }else{                                  //no coordinator and no speaker
                do{
                    if (!cin.good()){
                        cin.clear();
                        cin.ignore(numeric_limits<char>::max(), '\n');
                    }system("clear");
                    to_enroll->showDetails();
                    cout<<"\t[1]"<<" Join as coordinator\n\t[2] Join as speaker\n";
                    cin>>ws>>role_to_be;
                }while(!cin.good() || (role_to_be!='1' && role_to_be!='q'));
                if (role_to_be=='q'){
                    return;
                }else{
                    enroll(to_enroll, role(role_to_be-'1'));
                }
            }

        } else{
            if (!to_enroll->getspeaker()){          //coordinator but no speaker
                do{
                    if (!cin.good()){
                        cin.clear();
                        cin.ignore(numeric_limits<char>::max(), '\n');
                    }
                    system("clear");
                    to_enroll->showDetails();
                    cout<<"[1]"<<" Join as coordinator";
                    cin>>ws>>role_to_be;
                }while(!cin.good() || (role_to_be!='1' && role_to_be!='q'));
                if (role_to_be=='q'){
                    return;
                }else{
                    enroll(to_enroll, role::speaker);
                }
            }else{                                  //coordinator and speaker
                system("clear");
                to_enroll->showDetails();
                cout<<"\tAll roles occupied, you can not join to this seminar\n";
                cin.ignore(numeric_limits<char>::max(), '\n');
                cin.get();
            }
        }


        cout<<"You are already enrolled in this seminar"<<endl;
        cin.ignore(numeric_limits<int>::max(), '\n');
        cin.get();
        return;
    }

}



void Professor::seminar_view()
{

    string option_name;
    char willyougrade;
    Link_prof_res* selected_seminar = nullptr;

    vector<Menu<Link_prof_res>::Menu_option> seminar_selector_options;
    seminar_selector_options.reserve(seminarlist.size());

    unsigned i = 1;
    for (auto it: seminarlist){
        option_name = it->getResource()->getname()+" ID: "+it->getResource()->getIdentification();
        seminar_selector_options.emplace_back(i, nullptr, option_name.c_str(), (*it));
        i++;
    }

    string selector_name = "YOUR SEMINARS - Select the seminar you want to view";
    Menu<Link_prof_res> seminar_selector (seminar_selector_options, selector_name );

    selected_seminar = seminar_selector.run_selector();

    if (selected_seminar){
        Seminar* resourcePtr = dynamic_cast<Seminar*>(selected_seminar->getResource());
        if (selected_seminar->getRole()==role::coordinator){

            do {
                system("clear");
                if (!cin.good()){
                    cin.clear();
                    cin.ignore(numeric_limits<char>::max(), '\n');
                }
                selected_seminar->getResource()->showDetails();
                cout<<"\t[1] Edit \"q\" exit "<<endl;
                cin>>ws>>willyougrade;
            }while(!cin.good() && willyougrade!='q' && willyougrade!='1');

            //!cin.good() ||

            if (willyougrade == 'q'){
                return;
            }else{
                resourcePtr->coordinatorcanediteverythingbuttheid();
            }

        }else{
            Professor * coordinator = resourcePtr->getcoordinator()->getteacher();
            selected_seminar->getResource()->showDetails();
            cout<<"\tOnly the coordinator of this seminar can edit.\n\tIf you need to edit contact: "<< coordinator->getname()<<" ID: "<<coordinator->getidentifier()<<"\n\tor an administrator"<<endl;
            cin.ignore(numeric_limits<char>::max(), '\n');
            cin.get();
        }
    }
}



void Professor::showSeminars()
{
    unsigned i=1;
    for (auto it: seminarlist){
        cout<<" "<<i<<": "
           <<it->getResource()->getname()
          <<" ID: "<<it->getResource()->getIdentification()
         <<endl;
        i++;
    }
}



/* _______________________________________
  |                                       |
  |----------- FDP FUNCTIONS -------------|
  |_______________________________________|
*/



void Professor::manageFDP()
{
    vector<Menu<Professor>::Menu_option> options;
    options.reserve(2);
    options.emplace_back(1, &Professor::admin_addFDP, "Add FDP", this);
    options.emplace_back(2, &Professor::deleteFDP, "Delete FDP", this);


    Menu<Professor> menu(options, "FDPs:");

    menu.run();
}



void Professor::deleteFDP()
{
    char proceed;
    Link_prof_res *to_remove;
    string option_name;
    vector <Menu<Link_prof_res>::Menu_option> selector_options;
    selector_options.reserve(fdplist.size());
    unsigned i=1;
    for (auto it:fdplist ){
        option_name = it->getResource()->getname()+" ID: "+it->getResource()->getIdentification();
        selector_options.emplace_back(i, nullptr, option_name, (*it));
    }
    Menu<Link_prof_res> selector (selector_options, "Select the FDP you want to remove");

    to_remove=selector.run_selector();
    if (to_remove){
        if (to_remove->getRole()==role::tutor && dynamic_cast<FDP*>(to_remove->getResource())->getstudent()==nullptr){
            do{
                if (!cin.good()){
                    cin.clear();
                    cin.ignore(numeric_limits<char>::max(), '\n');
                }
                system("clear");
                cout<<"This FDP is not assigned to any student, if this professor is removed the FDP will be destroyed.\nProceed?(Y/N):";
                cin>>proceed;
            }while(!(proceed=='Y' || proceed=='y' || proceed=='N' || proceed=='n'));

            if (proceed=='Y' || proceed=='y'){
                for (auto it = mycampus->getFDPs().begin(); it!=mycampus->getFDPs().end(); it++)
                {
                    if (*it==to_remove->getResource()){
                        delete (*it);
                        mycampus->getFDPs().erase(it);
                        break;
                    }
                }

            }

        }else{
            delete to_remove;
        }
    }
}



void Professor::admin_addFDP()
{
    {
        char r;
        string identification;
        int valid=-1;
        do {
            system("clear");
            mycampus->showAllFDP();
            cout<<"Enter the id of the FDP you want to add or \'q\' to cancel\n";
            cin>>identification;
            if (identification == "q"){
                break;
            }
            valid=mycampus->findFDP(identification);
        }while(valid==-1);
        if (valid!=-1){
            do {
                system("clear");
                cout<<"Select Role:\n";
                cout<<"\n\t[1] Tutor\n\t[2] Co-tutor\n\t'q' Back";
                cin>>r;
                switch (r) {
                case '1':
                    enroll(mycampus->getFDPs()[unsigned(valid)], role::tutor);
                    return;
                case '2':
                    enroll(mycampus->getFDPs()[unsigned(valid)], role::tutor);
                    return;
                case 'q': return;
                default:
                    cout<<"Select a valid number"<<endl;
                    break;
                }

            }while(true);

        }
    }
}



void Professor::addFDP(Link_prof_res *link)
{
    this->fdplist.pushBack(link);
}



void Professor:: enroll(FDP* project, role r)
{
    Link_prof_res *newlink= new Link_prof_res (this, project, r);
    newlink->connectProftoFDP();
    newlink->connectResource();
}



void Professor::Drop(FDP* s)
{
    Link_prof_res link (this, s);
    for (unsigned i=0; i<fdplist.size(); i++){
        if (*fdplist[i]==link){
            delete fdplist[i];
        }
    }
}



void Professor::my_fdps()
{
    vector<Menu<Professor>::Menu_option> options;
    options.reserve(3);
    options.emplace_back(1, &Professor::fdp_view, "Select a FDP", this);
    options.emplace_back(2, &Professor::fdp_enrolling_func, "Enter a FDP", this);
    options.emplace_back(3, &Professor::fdp_droppin_func, "Leave a FDP", this);

    Menu<Professor> menu(options, "PROFFESOR "+name+" - Your Final Degree Projects", &Professor::showFDP, this);

    if(fdplist.size()>2){
        menu.set_settings({'q', menu_config::horizontal, 2, "Enter a valid option", '[', ']', false});
    }
    menu.run();
}



void Professor::fdp_droppin_func()
{
    Link_prof_res *to_drop;
    FDP *fdp_to_drop;
    string option_name;
    unsigned i=1;
    char proceed;

    vector<Menu<Link_prof_res>::Menu_option> options;

    options.reserve(fdplist.size());
    for (auto it:fdplist){
        option_name = it->getResource()->getname()+" ID: "+it->getResource()->getIdentification();
        options.emplace_back(i, nullptr, option_name, (*it));
        i++;
    }

    Menu<Link_prof_res> menu(options, "---YOUR FDPs---\n\tSelect the FDP you want to leave");

    to_drop=menu.run_selector();
    if(to_drop != nullptr){
        fdp_to_drop = dynamic_cast<FDP*>(to_drop->getResource());
        if (fdp_to_drop->getstudent()){
            Drop(fdp_to_drop);
        }else{
            do{
                if (!cin.good()){
                    cin.clear();
                    cin.ignore(numeric_limits<char>::max(), '\n');
                }
                system("clear");
                cout<<"Selected: "<<to_drop->getResource()->getname()
                   <<" ID: "<<to_drop->getResource()->getIdentification()
                  <<"\nThis Final Degree Project is not assigned to any student. If you leave it will be destroyed.\n"
                    "\nDo you want to proceed?(Y/N): "<<endl;
                cin>>proceed;
            }while(!(proceed=='Y' || proceed=='y' || proceed=='N' || proceed=='n'));

            if (proceed=='Y' || proceed=='y'){

                FDP* project_to_delete = dynamic_cast<FDP*> (to_drop->getResource());
                for (vector<FDP*>::iterator it =mycampus->getFDPs().begin();
                     it != mycampus->getFDPs().end(); it++ ){
                    if (*it==project_to_delete){
                        delete (*it);
                        mycampus->getFDPs().erase(it);
                        break;
                    }
                }


            }
        }
    }
}



void Professor::fdp_enrolling_func()
{
    FDP * to_enroll = nullptr; //Pointer to the fdp that this will be enrolled in. Will be assigned by the selector
    string option_name;
    unsigned i =1;
    vector<Menu<FDP>::Menu_option> options;
    options.reserve(mycampus->getFDPs().size());
    for (auto it:mycampus->getFDPs()){
        option_name = it->getname()+" ID: "+it->getIdentification();
        options.emplace_back(i, nullptr, option_name, (*it));
        i++;
    }

    Menu<FDP> menu(options, ("---FDPs AVAILABLE---"));
    char role_to_be;
    to_enroll = menu.run_selector();
    if (to_enroll){

        for (auto it : fdplist){
            if (it->getResource()  == to_enroll){                   //If the teacher is already tutor or co-tutor of this
                cout<<"You are already enrolled in this FDP"<<endl; //FDP we don't let them enroll
                cin.ignore(numeric_limits<int>::max(), '\n');
                cin.get();
                return;
            }
        }

        if (!to_enroll->gettutor()){
            if (to_enroll->getco_tutor()){            //no tutor but co-tutor
                do{
                    if (!cin.good()){
                        cin.clear();
                        cin.ignore(numeric_limits<char>::max(), '\n');
                    }
                    system("clear");
                    to_enroll->showDetails();
                    cout<<"\t[1]"<<" Join as tutor\n";
                    cin>>ws>>role_to_be;
                }while(!cin.good() || (role_to_be!='1' && role_to_be!='q'));
                if (role_to_be=='q'){
                    return;
                }else{
                    enroll(to_enroll, role::tutor);
                }

            }else{                                  //no tutor and no co-tutor
                do{
                    if (!cin.good()){
                        cin.clear();
                        cin.ignore(numeric_limits<char>::max(), '\n');
                    }system("clear");
                    to_enroll->showDetails();
                    cout<<"\t[1]"<<" Join as tutor\n\t[2] Join as co-tutor\n";
                    cin>>ws>>role_to_be;
                }while(!cin.good() || (role_to_be!='1' && role_to_be!='q'));
                if (role_to_be=='q'){
                    return;
                }else{
                    enroll(to_enroll, role(role_to_be-'1'+4));
                }
            }

        } else{
            if (!to_enroll->getco_tutor()){          //coordinator but no speaker
                do{
                    if (!cin.good()){
                        cin.clear();
                        cin.ignore(numeric_limits<char>::max(), '\n');
                    }
                    system("clear");
                    to_enroll->showDetails();
                    cout<<"[1]"<<" Join as coordinator";
                    cin>>ws>>role_to_be;
                }while(!cin.good() || (role_to_be!='1' && role_to_be!='q'));
                if (role_to_be=='q'){
                    return;
                }else{
                    enroll(to_enroll, role::cotutor);
                }
            }else{                                  //tutor and co-tutor
                system("clear");
                to_enroll->showDetails();
                cout<<"\tAll roles occupied, you can not join to this FDP\n";
                cin.ignore(numeric_limits<char>::max(), '\n');
                cin.get();
            }
        }
    }
}



void Professor::fdp_view()
{
    string option_name;
    char willyouedit;
    Link_prof_res* selected_fdp = nullptr;

    vector<Menu<Link_prof_res>::Menu_option> fdp_selector_options;
    fdp_selector_options.reserve(fdplist.size());

    unsigned i = 1;
    for (auto it: fdplist){
        option_name = it->getResource()->getname()+" ID: "+it->getResource()->getIdentification();
        fdp_selector_options.emplace_back(i, nullptr, option_name.c_str(), (*it));
        i++;
    }

    string selector_name = "YOUR FDPs - Select the fdp you want to view";
    Menu<Link_prof_res> fdp_selector (fdp_selector_options, selector_name );

    selected_fdp = fdp_selector.run_selector();

    if (selected_fdp){
        FDP* resourcePtr = dynamic_cast<FDP*>(selected_fdp->getResource());
        if (selected_fdp->getRole()==role::tutor){

            while(true){
                do {
                    system("clear");
                    if (!cin.good()){
                        cin.clear();
                        cin.ignore(numeric_limits<char>::max(), '\n');
                    }
                    selected_fdp->getResource()->showDetails();
                    cout<<"\t[1] Edit Name \"q\" exit "<<endl;
                    cin>>ws>>willyouedit;
                }while(!cin.good() && willyouedit!='q' && willyouedit!='1');

                //!cin.good() ||

                if (willyouedit == 'q'){
                    return;
                }else{
                    resourcePtr->editName();
                }
            }
        }else{
            selected_fdp->getResource()->showDetails();
            cin.ignore(numeric_limits<char>::max(), '\n');
            cin.get();
        }
    }
}



void Professor::showFDP()
{
    unsigned i=1;
    for (auto it: fdplist){
        cout<<" "<<i<<": "
           <<it->getResource()->getname()
          <<" ID: "<<it->getResource()->getIdentification()
         <<endl;
        i++;
    }
}



void Professor::showDetails()   //Function to show the details of a teacher
{
    cout<<"ID: "<<identifier<<endl;
    cout<<"Name: "<<this->name<<endl;
    cout<<"Courses: "<<courselist.size()<<endl;
    cout<<"Seminars: "<<seminarlist.size()<<endl;
    cout<<"FDPs: "<<fdplist.size()<<endl;
}



void Professor::edit()    //Edit Professor's attributes(name, id)
{
    char selection;

    do{
        system("clear");
        cout<<"PROFESSOR: "+name+" ID: "+identifier+" - edit\n\t[1] Edit name\n\t[2] Edit ID\n\t'q' Back\n";
        cin>>selection;
        switch (selection) {
        case '1':{
            string newname;
            bool valid=false;
            system("clear");
            cout<<"Enter the new name (letters a-z, A-Z) or \'q\' to cancel\n"<<endl;
            do {
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
        case'2':{
            string ident;
            bool valid=false;
            system("clear");
            cout<<"Enter the new ID (7 chars) or \'q\' to exit: ";
            do{
                cin>>ident;
                if (ident=="q"){
                    return;
                }
                if (ident.length()==7){
                    valid = true;
                }else{
                    system("clear");
                    cout<<"Enter the new ID (7 chars) or \'q\' to exit: ";
                }
            }while (!valid);

            if (valid){
                this->identifier=ident;
            }

            break;
        }
        case 'q':return;
        default:
            cout<<"Select a valid number\n";
            cin.ignore(numeric_limits<char>::max(), '\n');
            cin.get();
            break;

        }
    }while(true);

}



void Professor::options()    //Function of professor's options
{

    vector <Menu<Professor>::Menu_option> menu_options;
    menu_options.reserve(3);
    menu_options.emplace_back(1, &Professor::manageSeminars, "Manage seminars", this);
    menu_options.emplace_back(2, &Professor::manageCourses, "Manage courses", this);
    menu_options.emplace_back(3, &Professor::manageFDP, "Manage FDPs", this);
    menu_options.emplace_back(4, &Professor::edit, "Edit", this);
    Menu<Professor> menu (menu_options, "PROFESSOR: ", &Professor::showDetails, this);
    menu.run();

}



void Professor::menu()
{
    vector<Menu<Professor>::Menu_option> options;
    options.reserve(3);
    options.emplace_back(1, &Professor::my_courses, "Manage Courses", this);
    options.emplace_back(2, &Professor::my_seminars, "Manage Seminars", this);
    options.emplace_back(3, &Professor::my_fdps, "Manage FDPs", this);

    Menu<Professor> menu(options, "---WELCOME TO YOUR MAIN MENU---", &Professor::showDetails, this);

    menu.run();
}



/* _______________________________________
  |                                       |
  |-------------FILE HANDLING-------------|
  |_______________________________________|
*/



ofstream& Professor::loadtofile(ofstream & file)
{
    file<<*this;
    return file;
}



ofstream & operator<< (ofstream& ofs, Professor& _professor)
{
    char id[8];
    bool isadmin = false;
    ofs.write(reinterpret_cast<char*>(&isadmin), sizeof (bool));
    ofs << &_professor;
    strcpy(id,_professor.identifier.c_str());
    ofs.write(id,  8 * sizeof (char));
    unsigned long seminar_number = _professor.seminarlist.size();
    unsigned long course_number = _professor.courselist.size();
    unsigned long fdp_number = _professor.fdplist.size();
    ofs.write(reinterpret_cast<char*>(&seminar_number), sizeof(unsigned long));
    ofs.write(reinterpret_cast<char*>(&course_number), sizeof(unsigned long));
    ofs.write(reinterpret_cast<char*>(&fdp_number), sizeof(unsigned long));
    return ofs;
}



ifstream& operator>>(ifstream& ifs, Professor& _professor)
{
    ifs>>&_professor;
    char id [8];
    ifs.read(id, 8 * sizeof (char));
    _professor.identifier=id;

    unsigned long seminar_number = _professor.seminarlist.size();
    unsigned long course_number = _professor.courselist.size();
    unsigned long fdp_number = _professor.fdplist.size();
    ifs.read(reinterpret_cast<char*>(&seminar_number), sizeof(unsigned long));
    ifs.read(reinterpret_cast<char*>(&course_number), sizeof(unsigned long));
    ifs.read(reinterpret_cast<char*>(&fdp_number), sizeof(unsigned long));
    _professor.seminarlist.reserve(seminar_number);
    _professor.courselist.reserve(course_number);
    _professor.fdplist.reserve(fdp_number);
    return ifs;
}
