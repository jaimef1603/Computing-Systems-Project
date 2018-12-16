#include "VirtualCampus.h"
#include "Utilities.h"
#include <sstream>
#include "Menu.h"
#include <iostream>

using namespace std;

VirtualCampus::VirtualCampus(string dat)
{

    data_dir = new char[dat.length()+1];
    strcpy(data_dir, dat.c_str());
    currentuser=nullptr;

}



VirtualCampus::~VirtualCampus()
{

    if (currentuser){
        if(currentuser->getidentifier()=="adminis"){
            delete currentuser;
        }
    }

    if (data_dir)
        delete [] data_dir;

    if (degreelist.size()>0){
        for (Degree * element: degreelist){

            delete element;
        }
    }


    if (seminalist.size()>0){
        for (Seminar * element: seminalist){

            delete element;
        }
    }


    if (projectlist.size()>0){
        for (FDP * element: projectlist){
            delete element;
        }
    }


}



void VirtualCampus::run()   //Function to start the program
{

    if (currentuser)
        currentuser->menu();

}



void VirtualCampus::start()
{

    string ident;
    if (login(ident)){

        ifstream directory("Data/", ios::in);
        if (!directory){
            cerr<<"Creating data directory";
            system("mkdir ./Data");
        }else{
            directory.close();
            directory.open("Data/.~"+string(data_dir)+".lock");
            if (directory){
                recover=true;
                directory.close();
            }

        }
        loadTeachers();
        loadFDPs();
        loadSeminars();
        loadDegrees();
        system(("touch Data/.~"+string(data_dir)+".lock").c_str());

        if (ident != "ADMIN"){
            for(auto _prof: proflist){
                if(_prof->getidentifier()==ident){
                    currentuser = _prof;
                    return;
                }
            }

            for(auto _deg:degreelist){
                for(auto _stu: _deg->getStudents()){
                    if(_stu->getidentifier()==ident){
                        currentuser = _stu;
                        return;
                    }
                }
            }
            cerr<<"User not found, missmatch in database\n";
        }
    }

    cin.get();
}



void VirtualCampus::stop()
{

    writeTeachers();
    writeDegrees();
    writeSeminars();
    writeFDPs();

    system(("rm Data/.~"+string(data_dir)+".lock").c_str());
    cin.get();
}



/* _______________________________________
  |                                       |
  |---------- DEGREE FUNCTIONS------------|
  |_______________________________________|
*/



void VirtualCampus::manageDegrees()
{
    string buffer;
    char selection='0';
    int deg;
    do{
        if (selection=='0'){
            system("clear");
            showAllDeg();
            cout<<"\nManage Degrees\n"<<endl;
            cout<<"\t[1] Create Degree\n \t[2] Edit Degree\n \t[3] Delete Degree\n \t[4] Details Degree\n \t[5] Select Degree\n \t'q' Back\n";
            cin>>selection;
        }
        switch(selection){
        case '1':
            selection='0';
            addDegree();
            system("clear");
            if (degreelist.size()>0){

                (*(degreelist.end()-1))->showdetails();
                cin.ignore(1, '\n');
                cin.get();
            }
            break;
        case '2':
            selection='0';
            do {
                system("clear");
                showAllDeg();
                cout<<"What degree do you want to edit? (Enter (1-"<< degreelist.size()<<")to edit or \'q\' to cancel)\n";
                cin>>ws>>buffer;
                if(buffer=="q"){
                    return;
                }
                istringstream(buffer)>>deg;
                if (deg >int(degreelist.size())){
                    cout<<"Select a valid number. (1-"<<degreelist.size()<<") or \'q\' to cancel\nPress any key to retry...";
                    getchar();
                }
            }while(deg >int(degreelist.size()));
            system("clear");
            if (deg!='q'){
                degreelist[unsigned(deg)-1]->edit();
            }
            break;
        case '3':
            selection='0';
            do {
                system("clear");
                showAllDeg();
                cout<<"What degree do you want to delete? (Enter (1-"<< degreelist.size()<<")to delete or \'q\' to cancel)\n";
                cin>>ws>>buffer;
                if(buffer=="q"){
                    return;
                }
                istringstream(buffer)>>deg;
                if (deg >int(degreelist.size())){
                    cout<<"Select a valid number. (0-"<<degreelist.size()<<") or \'q\' to cancel\nPress any key to retry...";
                    getchar();
                }
            }while(deg >int(degreelist.size()));
            system("clear");
            if (deg!='q'){
                deleteDegree(unsigned(deg)-1);
            }
            break;
        case '4':
            selection='0';
            do {
                system("clear");
                showAllDeg();
                cout<<"What degree do you want to show details of? (Enter (1-"<< degreelist.size()<<")to show details or \'q\' to cancel)\n";
                cin>>ws>>buffer;
                if(buffer=="q"){
                    return;
                }
                istringstream(buffer)>>deg;
                if (deg >int(degreelist.size())){
                    cout<<"Select a valid number. (0-"<<degreelist.size()<<") or \'q\' to cancel\nPress any key to retry...";
                    getchar();
                }
            }while(deg >int(degreelist.size()));
            system("clear");
            if (deg!='q'){
                degreelist[unsigned(deg)-1]->showdetails();
                cout<<"Press any key to exit\n";
                cin.ignore(90, '\n');
                getchar();
            }

            break;
        case '5':
            selection='0';
            do {
                system("clear");
                showAllDeg();
                cout<<"What degree do you want to select? (Enter (1-"<< degreelist.size()<<")to select or \'q\' to cancel)\n";
                cin>>ws>>buffer;
                if(buffer=="q"){
                    return;
                }
                istringstream(buffer)>>deg;
                if (deg >int(degreelist.size())){
                    cout<<"Select a valid number. (0-"<<degreelist.size()<<") or \'q\' to cancel\n";
                }
            }while(deg >int(degreelist.size()));
            system("clear");
            if (deg!='q'){
                degreelist[unsigned(deg)-1]->options();
            }
            break;
        case 'q' : return;

        default:
            system("clear");
            showAllDeg();
            cout<<"\t[1] Create\n \t[2] Edit\n \t[3] Delete\n \t[4] Details\n \t[5] Select\n \t'6' Back\n";
            cout<<"Enter a valid number(1-5) or \'q\' to cancel\n"<<endl;
            cin>>selection;
            break;
        }
    }while(true);

}



void VirtualCampus::addDegree()
{
    system("clear");
    bool valid = true;
    string id;
    string name;
    do{
        system("clear");
        cout<<"Enter the name of the degree (letters a-z, A-Z) or \'q\' to cancel:";
        cin.ignore(numeric_limits<char>::max(), '\n');

    }while(!getline(cin, name ,'\n') || !checkletters(name));         //we continue asking for the name until all the characters are letters
    if (name =="q"){
        return;
    }

    do{
        valid=true;
        system("clear");
        cout<<"Name: "<<name<<endl;
        cout<<"Enter the three letter identification or \'q\' to cancel: ";
        cin>>ws>>id;
        if (id=="q"){
            return;
        }

        if (!checkletters(id) || id.length()!=3){       //if the id characters are not letters or the length is not 3
            valid = false;                              //we change valid to false
        }else{                                          //if the id characters are only letters and the length is 3 we continue
            UCaseWord(id);                              //we change the id to uppercase
            if(id=="SEM" || id=="FDP"){                 //we check if the id is different of the id reserved for other resources
                valid = false;
                cout<<"\"SEM\" and \"FDP\" are system reserved identifications, please choose another"<<endl;
                cin.ignore(numeric_limits<char>::max(), '\n');
                cin.get();
            }else{                                       //if the id is different from the one reserved
                for (auto it: degreelist){               //we check if there is already a degree with that identification

                    if (it->getid()==id){                //if it is, we change valid to false
                        valid = false;
                        cout<<"There is already a degree with this identification, choose another"<<endl;
                        cin.ignore(numeric_limits<char>::max(), '\n');
                        cin.get();
                        break;
                    }

                }
            }

        }

    }while(!valid);
    degreelist.push_back(new Degree(this, name, id.c_str()));

}



void VirtualCampus::deleteDegree(unsigned index)
{

    delete degreelist[index];
    degreelist.erase(degreelist.begin()+index);

}



int VirtualCampus::findDegree(string identification)   //Function to find a degree in the degreelist if it is created, and return the position where it is
{

    for (unsigned i=0; i<degreelist.size(); i++ ){
        if (degreelist[i]->getid()==identification){
            return int(i);
        }
    }
    return -1;

}



void VirtualCampus::showAllDeg()     //Function to show all the degrees
{
    cout<<"DEGREES:\n";
    if (degreelist.size()>0){
        for(unsigned i=0;i<degreelist.size();i++){
            cout<<i+1<<": "<<degreelist[i]->getname()<<endl;
        }
    }else{
        cout<<"\n";
    }
}



vector <Degree*>& VirtualCampus::getDegrees()
{
    return degreelist;
}



/* _______________________________________
  |                                       |
  |----------PROFESSOR FUNCTIONS----------|
  |_______________________________________|
*/



void VirtualCampus::manageTeachers()
{
    char selection;
    do{
        system("clear");
        cout<<"Manage teachers\n"<<endl;
        cout<<"\t[1] Create teacher (or Administrator)\n\t[2] Delete teacher\n\t[3] Show details\n\t'q' Back"<<endl;
        cin>>selection;
        switch (selection) {
        case '1':
            addTeacher();
            break;
        case '2':
        {
            Professor *to_delete;
            vector<Menu<Professor>::Menu_option> e_s_options;
            e_s_options.reserve(proflist.size());
            unsigned i=1;
            for (auto it: proflist){
                e_s_options.emplace_back(i, nullptr,
                                         it->getname()+"\tID: "+it->getidentifier(), (*it));
                i++;
            }

            Menu<Professor> edit_selector(e_s_options, "Select the teacher you want to delete or \'q\' to cancel");
            to_delete=edit_selector.run_selector();
            if (to_delete){
                if (to_delete!=currentuser){
                    unsigned i=0;
                    for (vector<Professor*>::iterator it = proflist.begin(); it!=proflist.end(); it++ , i++){
                        if (*it == to_delete){
                            delete to_delete;
                            proflist.erase(it);
                            break;
                        }
                    }
                }else{
                    cout<<"You cannot delete yourself!"<<endl;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin.get();

                }
            }
        }
            break;

        case '3':
        {
            vector<Menu<Professor>::Menu_option> e_s_options;
            e_s_options.reserve(proflist.size());
            unsigned i=1;
            for (auto it: proflist){
                e_s_options.emplace_back(i, &Professor::options,
                                         it->getname()+"\tID: "+it->getidentifier(), (*it));
                i++;
            }

            Menu<Professor> edit_selector(e_s_options, "Select a teacher or \'q\' to cancel");
            edit_selector.run();
        }
            break;

        case 'q': return;
        default:
            cout<<"Enter a valid number(1-3) or \'q\' to cancel"<<endl;
        }
    }while(true);
}



void VirtualCampus::addTeacher()
{

    system("clear");
    bool valid=false;
    string ident, name;
    char permissions;

    std::string buffer; //Auxiliar string to prevent buffer loops and incorrect insertions


    //---- ASKING FOR THE NAME OF THE PROFESSOR-----

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do {
        system("clear");
        if (!cin.good()){
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout<<"Enter the name or \'q\' to cancel: ";

    }while(!getline(cin, name, '\n') || (!checkletters(name) && name!="q"));      //we continue asking the name until its characters are letters

    if (name=="q"){
       return;         //If "q" was inserted we abort
    }

    // ----ASKING FOR THE ID-----

    system("clear");
    cout<<"Enter the new ID (7 chars) or \'q\' to cancel: ";
    do{
        valid = true;
        cin>>ident;
        if (ident=="q"){
            return;
        }

        if ((ident.length()!=7)){
            valid = false;
            system("clear");
            cout<<"Enter the new ID (7 chars) or \'q\' to cancel: ";
        }else{
            for (auto it: proflist){                    //we check if there is already a teacher with that identification
                if (it->getidentifier()==ident){        //if it is, we change vaid to false
                    valid = false;
                    system("clear");
                    cout<<"ID already used, choose a different one\n";
                    cout<<"Enter the new ID (7 chars) or \'q\' to cancel: ";
                }
            }
        }
    }while (!valid);

    //-----WE KEEP ASKING WHILE THE INSERTION IS
    //CORRECT; THE FORMAT IS CORRECT AND IT IS NOT "q"

    do {
        if(!cin.good()){
            cin.clear();
            cin.ignore(numeric_limits<char>::max(), '\n');
        }
        system("clear");
        cout<<"\t[1] Create as teacher\n\t[2] Create as administrator\n\t\'q\' Back\n";
        cin>>ws>>permissions;
    }while(permissions != '1' && permissions != '2' && permissions!='q');


    //we create a professor or an administrator according to the role selected

    if (permissions=='1'){
        proflist.push_back(new Professor (this, name, ident));
    }else if (permissions=='2'){
        proflist.push_back(new Administrator (this, name, ident));
    }

}



int VirtualCampus::findTeacher(string identification)    //Function to find a teacher in the proflist if it is created, and return the position where it is
{

    for (unsigned i=0; i<proflist.size(); i++ ){
        if (proflist[i]->getidentifier()==identification){
            return int(i);
        }
    }
    return -1;

}



vector <Professor*>& VirtualCampus::getTeachers()
{
    return proflist;
}



void VirtualCampus::showAllTeach()   //Function to show all the teachers
{
    cout<<"TEACHERS:\n";
    if (proflist.size()>0){
        for(unsigned i=0;i<proflist.size();i++){

            cout<<i+1<<": "<<proflist[i]->getidentifier()<<endl;
        }
    }else{
        cout<<"\n";
    }
}



/* _______________________________________
  |                                       |
  |---------- SEMINAR FUNCTIONS-----------|
  |_______________________________________|
*/



void VirtualCampus::manageSeminars()
{

    vector<Menu<VirtualCampus>::Menu_option> options;


    options.push_back(Menu<VirtualCampus>::Menu_option (1, &VirtualCampus::addseminar, "Add Seminar", this));
    options.push_back(Menu<VirtualCampus>::Menu_option (2, &VirtualCampus::selectSeminar, "Select Seminar", this));
    options.push_back(Menu<VirtualCampus>::Menu_option (3, &VirtualCampus::deleteSeminar, "Delete Seminar", this));


    Menu<VirtualCampus> seminarMenu(options,"Manage Seminars", &VirtualCampus::showAllSeminars, this);

    if (seminalist.size()>2){
        seminarMenu.set_settings({ 'q', menu_config::horizontal, 1, "Enter a valid option", '[', ']', false });
    }
    seminarMenu.run();

}



void VirtualCampus::addseminar()
{
    system("clear");
    bool valid;
    string id, name;
    Professor* Coord;
    unsigned day, month, year;
    Date when;
    unsigned seats;

    std::string buffer; //Auxiliar string to prevent buffer loops and incorrect insertions


    //---- ASKING FOR THE NAME OF THE SEMINAR-----

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do {
        system("clear");
        if (!cin.good()){
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }


        std::cout<<"Enter the name of the new seminar or \'q\' to cancel: ";

    }while(!getline(cin, buffer, '\n') || (!checkletters(buffer) && buffer!="q"));

    if (buffer!="q"){
        name=buffer;
    }else{
        return;     //If "q" was inserted we abort
    }


    // ----ASKING FOR THE ID-----

    do {
        system("clear");
        valid = true;
        if (!cin.good()){
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout<<"Name: "<<name<<"\nEnter the identification (CCCIIII, C=Letter, I=Number) or \'q\' to cancel: \nSEM";

        //we check if the id is correct (SEMCCCC)

        if (!(std::cin>>std::ws>>buffer) || (!checkResId("SEM"+buffer) && buffer !="q")){
            valid = false;                            //if it is not correct, we change valid to false
        }else{                                        //we check if there is already a seminar with that identification
            for (auto it: seminalist){
                if (it->getIdentification()=="SEM"+buffer){      //if there is, we change valid to false
                    valid = false;
                    cout<<"There is already a seminar with this identification, choose another"<<endl;
                    cin.ignore(numeric_limits<char>::max(), '\n');
                    cin.get();
                }

            }

        }
    }while(!valid);

    //-----WE KEEP ASKING WHILE THE INSERTION IS
    //CORRECT; THE FORMAT IS CORRECT AND IT IS NOT "q"

    if (buffer!="q"){
        id="SEM"+buffer;
    }else{
        return; //IF "q" was inserted we abort
    }


    //----- ASKING FOR THE MAXIMUM NUMBER OF SEATS----

    do {
        system("clear");
        if (!cin.good()){
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout<<"Name: "<<name<<"\nID: "<<id<<"\nEnter the value for the maximum number of seats or \'q\' to cancel:";
        std::cin>>std::ws>>buffer;

        if (buffer=="q"){
            return;
        }

    }while(!(istringstream(buffer)>>seats));


    //----ASKING FOR THE DATE------

    do {
        system("clear");
        if (!cin.good()){
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout<<"Name: "<<name<<"\nID: "<<id<<"\nSeats: "<<seats<<"\nEnter the event date (day month year) or \'q\' to cancel:";
        getline(std::cin, buffer, '\n');

        if (buffer=="q"){
            return;
        }

    }while(!(istringstream(buffer)>>day>>month>>year));
    when = Date(day, month, year);

    //WE CREATE A SELECTOR TO SELECT THE TEACHER

    string selector_name
            = "Name: "+name
            +"\nID: "+id
            +"\nSeats: "+to_string(seats)
            +"\nDate: "+when.getfancyDate();

    if (proflist.size()>0){
        selector_name+="\nSelect a teacher to be the coordinator";

        Menu<Professor> CoordSelector(proflist, User::gimmethename(), selector_name);
        Coord=CoordSelector.run_selector();
        if (!Coord)
            return;


        // IF WE DIDN'T ABORT WE CREATE THE NEW SEMINAR

        seminalist.push_back(new Seminar(this, name, id, seats, Coord, Date (day, month, year)));
    }else{
        system("clear");
        selector_name+="\nCreate a teacher first to be the coordinator, Seminar not created\n";
        cout<<selector_name;
        cin.ignore(numeric_limits<char>::max(), '\n');
        cin.get();
    }


}



void VirtualCampus::deleteSeminar()
{

    Menu<Seminar> deleteSelector(seminalist, Resource::gimmetheid());
    Seminar *to_remove=deleteSelector.run_selector();
    if (to_remove){
        for (auto it = seminalist.begin(); it!=seminalist.end(); it++){
            if ((*it)==to_remove){
                seminalist.erase(it);
                break;
            }
        }
        delete to_remove;
    }
}



void VirtualCampus::selectSeminar()
{
    Menu<Seminar> optionsMenu(seminalist, &Seminar::options, Seminar::gimmetheid(), "SEMINAR - select");
    optionsMenu.run();
}



int VirtualCampus::findSeminar(string identification)    //Function to find a seminar in the seminalist if it is created, and return the position where it is
{
    for (unsigned i=0; i<seminalist.size(); i++){
        if (identification==seminalist[i]->getIdentification()){
            return int(i);
        }
    }

    return -1;
}



void VirtualCampus::showAllSeminars()        //Function to show all the seminars
{

    for(unsigned i=0;i<seminalist.size();i++){
        cout<<i+1<<": "<<endl;
        cout<<"   ID: "<<seminalist[i]->getIdentification()<<endl;
        cout<<"   Name: "<<seminalist[i]->getname()<<endl;
    }
    cout<<endl;

}



vector<Seminar*>& VirtualCampus::getSeminars()
{
    return seminalist;
}



/* _______________________________________
  |                                       |
  |------------FDP FUNCTIONS--------------|
  |_______________________________________|
*/



void VirtualCampus::manageFDPs()
{

    vector<Menu<VirtualCampus>::Menu_option> options;

    options.push_back(Menu<VirtualCampus>::Menu_option (1, &VirtualCampus::addFDP, "Add FDP", this));
    options.push_back(Menu<VirtualCampus>::Menu_option (2, &VirtualCampus::selectFDP, "Select FDP", this));
    options.push_back(Menu<VirtualCampus>::Menu_option (3, &VirtualCampus::deleteFDP, "Delete FDP", this));


    Menu<VirtualCampus> seminarMenu(options,"Manage FDP", &VirtualCampus::showAllFDP, this);
    seminarMenu.run();

}



void VirtualCampus::addFDP()
{
    system("clear");
    string id, name;
    Degree *temp_degree = nullptr;
    Professor* temp_professor = nullptr;
    Student *temp_student = nullptr;

    std::string buffer; //Auxiliar string to prevent buffer loops and incorrect insertions


    // ----ASKING FOR THE ID-----


    do {
        system("clear");
        if (!cin.good()){
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout<<"Enter the identification (CCCIIII, C=Letter, I=Number) or \'q\' to cancel: \nFDP";

    }while(!(std::cin>>std::ws>>buffer) || (!checkResId("FDP"+buffer) && buffer !="q"));

    if (buffer!="q"){
        id="FDP"+buffer;
    }else{
        return; //If "q" was inserted we abort
    }


    //---- ASKING FOR THE NAME OF THE FDP-----


    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do {
        system("clear");
        if (!cin.good()){
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout<<"Enter the title or \'q\' to cancel: ";

    }while(!getline(cin, buffer, '\n') || (!checkletters(buffer) && buffer!="q"));

    if (buffer!="q"){
        name=buffer;
    }else{
        return;    //If "q" was inserted we abort
    }


    Menu<Degree> degree_selector(degreelist, Degree::gimme_the_name(), "Select a degree to select a student or \'q\' to leave it blank");

    temp_degree = degree_selector.run_selector();
    if (temp_degree){

        vector <Menu<Student>::Menu_option> Student_selector_options;

        for (unsigned i= 0; i< temp_degree->getStudents().size(); i++){
            Student_selector_options.push_back(Menu<Student>::Menu_option(i+1, nullptr, temp_degree->getStudents()[i]->getname()+ " ID: "+temp_degree->getStudents()[i]->getidentifier(), temp_degree->getStudents()[i]));
        }


        Menu<Student> Student_selector (Student_selector_options, "Select the student or \'q\' to leave it blank");
        temp_student= Student_selector.run_selector();
    }


    vector <Menu<Professor>::Menu_option> professor_selector_options;

    for (unsigned i= 0; i< proflist.size(); i++){
        professor_selector_options.push_back(Menu<Professor>::Menu_option(i+1, nullptr, proflist[i]->getname()+ " ID: "+proflist[i]->getidentifier(), proflist[i]));
    }

    if (temp_student){  //If temp_student != nullptr it means the user selected a student and didnt abort pressing q
        //so we let them leave the tutor field blank

        Menu<Professor> professor_selector (professor_selector_options, "Select the teacher or \'q\' to leave it blank");

        temp_professor= professor_selector.run_selector();

        projectlist.push_back(new FDP(this, name, id, temp_student, temp_professor));

    }else{ //But if the user didnt select a student and they don't select a professor we abort

        Menu<Professor> professor_selector (professor_selector_options, "You must select a teacher or \'q\' to cancel");

        temp_professor= professor_selector.run_selector();

        if (temp_professor){
            projectlist.push_back(new FDP(this, name, id, temp_student, temp_professor));
        }
    }

}



void VirtualCampus::selectFDP()
{
    Menu<FDP> optionsMenu(projectlist, &FDP::options, FDP::gimmetheid(), "Final Degree Project - select");
    optionsMenu.run();
}



void VirtualCampus::deleteFDP()
{
    Menu<FDP> deleteSelector(projectlist, Resource::gimmetheid());
    FDP *to_remove=deleteSelector.run_selector();
    if (to_remove){
        for (vector<FDP*>::iterator it = projectlist.begin(); it!=projectlist.end(); it++){
            if ((*it)==to_remove){
                projectlist.erase(it);
                break;
            }
        }
        delete to_remove;
    }
}



vector <FDP*>& VirtualCampus::getFDPs()
{
    return projectlist;
}



int VirtualCampus::findFDP(string identification)
{

    for (unsigned i=0; i<projectlist.size(); i++){
        if (identification==projectlist[i]->getIdentification()){
            return int(i);
        }
    }

    return -1;
}



void VirtualCampus::showAllFDP()
{
    for(unsigned i=0;i<projectlist.size();i++){
        cout<<i+1<<": "<<endl;
        cout<<"   ID: "<<projectlist[i]->getIdentification()<<endl;
        cout<<"   Title: "<<projectlist[i]->getname()<<endl;
    }
    cout<<endl;
}



// File handling

#include "VirtualCampusFiles.tpp"



