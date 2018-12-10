#include "VirtualCampus.h"
#include "Utilities.h"
#include <sstream>
#include "Menu.h"

VirtualCampus::VirtualCampus()
{

    currentuser=new Administrator("undefined","aaaaaa", this);

}



VirtualCampus::~VirtualCampus()
{
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

    if (currentuser!=nullptr){
        delete currentuser;         //QUITAR CUANDO SE PUEDA SELECCIONAR USUARIO
    }
}



int VirtualCampus::run()   //Function to start the program
{

    int selection;
    while(true){
        fflush(stdout);
        system("clear");
        cout<<"1: Log in as student 2: Log in as administrator"<<endl;
        cin>>selection;
        switch (selection)
        {

        case 1:
            if(degreelist.size()>0 ){
                if (degreelist[0]->getStudents().size()>0){

                    currentuser = degreelist[0]->getStudents()[0];
                    break;
                }
            }else{
                cerr<<"NO STUDENT HAS BEEN YET CREATED; LOGGING IN AS ADMINISTRATOR\n";
                cin.ignore(50, '\n');
                cin.get();

            }
        [[clang::fallthrough]];
        case 2:
            currentuser = new Administrator("ADMIN", "adminis", this); break;
        }
        system("clear");
        currentuser->menu();
    }


    return 1;
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
            cout<<"1: Create 2: Edit 3: Delete 4: Details 5: Select 6:Back\n";
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
                //cout<<"DEGREES:\n";
                showAllDeg();
                cout<<"What degree do you want to edit?\n";
                cin>>ws>>buffer;
                istringstream(buffer)>>deg;
                if ((deg<1 && deg!=-1) || deg >int(degreelist.size())){
                    cout<<"Select a valid number. (0-"<<degreelist.size()<<") or -1 to exit\nPress any key to retry...";
                    getchar();
                }
            }while((deg<1 && deg!=-1) || deg >int(degreelist.size()));
            system("clear");
            if (deg!=-1){
                degreelist[unsigned(deg)-1]->edit();
            }
            break;
        case '3':
            selection='0';
            do {
                system("clear");
                //cout<<"DEGREES:\n";
                showAllDeg();
                cout<<"What degree do you want to delete?\n";
                cin>>ws>>buffer;
                istringstream(buffer)>>deg;
                if ((deg<1 && deg!=-1) || deg >int(degreelist.size())){
                    cout<<"Select a valid number. (0-"<<degreelist.size()<<") or -1 to exit\nPress any key to retry...";
                    getchar();
                }
            }while((deg<1 && deg!=-1) || deg >int(degreelist.size()));
            system("clear");
            if (deg!=-1){
                deleteDegree(unsigned(deg)-1);
            }
            break;
        case '4':
            selection='0';
            do {
                system("clear");
                showAllDeg();
                cout<<"What degree do you want to show details of?\n";
                cin>>ws>>buffer;
                istringstream(buffer)>>deg;
                if ((deg<1 && deg!=-1) || deg >int(degreelist.size())){
                    cout<<"Select a valid number. (0-"<<degreelist.size()<<") or -1 to exit\nPress any key to retry...";
                    getchar();
                }
            }while((deg<1 && deg!=-1) || deg >int(degreelist.size()));
            system("clear");
            if (deg!=-1){
                degreelist[unsigned(deg)-1]->showdetails();
                cout<<"Press any key to exit\n";
                cin.ignore(90, '\n');
                getchar();
            }
            //system("clear");
            break;
        case '5':
            selection='0';
            do {
                system("clear");
                showAllDeg();
                cout<<"What degree do you want to select?\n";
                cin>>ws>>buffer;
                istringstream(buffer)>>deg;
                if (deg<1 || deg >int(degreelist.size())){
                    cout<<"Select a valid number. (0-"<<degreelist.size()<<") or -1 to exit\n";
                }
            }while((deg<1 && deg!=-1)|| deg >int(degreelist.size()));
            system("clear");
            if (deg!=-1){
                degreelist[unsigned(deg)-1]->options();
            }
            break;
        case '6': return;

        default:
            system("clear");
            showAllDeg();
            cout<<"1: Create 2: Edit 3: Delete 4:Details 5: Select 6:Back\n";
            cout<<"Enter a valid number(1-6)\n"<<endl;
            cin>>selection;
            break;

        }
    }while(true);

}



void VirtualCampus::addDegree()
{
    system("clear");
    bool valid = true;
    string name, id;
    cout<<"Enter the name of the degree (letters a-z, A-Z) or \"cancel\" to exit : ";
    do{
        cin>>ws>>name;
        if (name =="cancel"){
            return;
        }
    }while(!checkletters(name));
    do{
        valid=true;
        system("clear");
        cout<<"Name: "<<name<<endl;
        cout<<"Enter the three letter identification or write \"cancel\" to exit: ";
        cin>>ws>>id;
        if (id=="cancel"){
            return;
        }

        if (!checkletters(id) || id.length()!=3){
            valid = false;
        }else{
            UCaseWord(id);
            for (auto it: degreelist){

                if (it->getid()==id){
                    valid = false;
                    cout<<"There is already a degree with this identification, choose another"<<endl;
                    cin.ignore(numeric_limits<char>::max(), '\n');
                    cin.get();
                }

            }

        }

    }while(!valid);
    degreelist.push_back(new Degree(name, id.c_str(), this));

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
        cout<<"1: Create teacher 2: Edit teacher 3: Delete teacher 4: Details 5: Select 6: Back"<<endl;
        cin>>selection;
        switch (selection) {
        case '1': addTeacher(); break;
        case '2': {
            string id;
            int teach=-1;
            system("clear");
            showAllTeach();
            cout<<"Enter the id of the teacher you want to edit.\n";

            do {
                cin>>ws>>id;
                if (id=="cancel"){
                    break;
                }else{
                    teach=findTeacher(id);
                }
                if(teach==-1){
                    system("clear");
                    cout<<"Invalid ID\n";
                    cout<<"Enter the id of the teacher you want to edit\n";
                }
            }while(teach==-1);
            system("clear");
            if (teach!=-1){
                proflist[unsigned(teach)]->edit();
            }
        }break;
        case '3':
        {
            string id;
            int teach=-1;
            system("clear");
            showAllTeach();
            cout<<"Enter the id of the teacher you want to delete.\n";

            do {
                cin>>ws>>id;
                if (id=="cancel"){
                    break;
                }else{
                    teach=findTeacher(id);
                }
                if(teach==-1){
                    system("clear");
                    cout<<"Invalid ID\n";
                    cout<<"Enter the id of the teacher you want to delete.\n";
                }
            }while(teach==-1);
            system("clear");
            if (teach!=-1){
                deleteTeacher(unsigned(teach));
            }
        }
            break;
        case '4': {
            string id;
            int teach=-1;
            system("clear");
            cout<<"Enter the id of the teacher you want to show details of.\n";

            do {
                cin>>ws>>id;
                if (id=="cancel"){
                    break;
                }else{
                    teach=findTeacher(id);
                }
                if(teach==-1){
                    system("clear");
                    cout<<"Invalid ID\n";
                    cout<<"Enter the id of the teacher you want to show details of.\n";
                }
            }while(teach==-1);
            system("clear");
            if (teach!=-1){
                proflist[unsigned(teach)]->showdetails();
                cin.ignore(std::numeric_limits<int>::max(), '\n');
                cin.get();
            }
        }break;

        case '5':
        {
            string id;
            int teach=-1;
            system("clear");
            cout<<"Enter the id of the teacher you want to select.\n";

            do {
                cin>>ws>>id;
                if (id=="cancel"){
                    break;
                }else{
                    teach=findTeacher(id);
                }
                if(teach==-1){
                    system("clear");
                    cout<<"Invalid ID\n";
                    cout<<"Enter the id of the teacher you want to select.\n";
                }
            }while(teach==-1);
            system("clear");
            if (teach!=-1){
                proflist[unsigned(teach)]->options();
            }
        }
            break;

        case '6': return;
        default:
            cout<<"Enter a valid number(1-6)."<<endl;
        }
    }while(true);
}



void VirtualCampus::addTeacher()
{







    system("clear");
    bool valid=false;
    string ident, name;

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
        if (name=="q"){
            return;
        }

    }while(!getline(cin, name, '\n') || !checkletters(name));




    // ----ASKING FOR THE ID-----

    system("clear");
    cout<<"Enter the new ID (7 chars) or \'q\' to exit: ";
    do{
        valid = true;
        cin>>ident;
        if (ident=="q"){
            return;
        }

        if ((ident.length()!=7) || (!checkletters(ident))){
            valid = false;
            system("clear");
            cout<<"Enter the new ID (7 chars) or \'q\' to exit: ";
        }else{
            for (auto it: proflist){
                if (it->getidentifier()==ident){
                    valid = false;
                    system("clear");
                    cout<<"ID already used, choose a different one\n ";
                    cout<<"Enter the new ID (7 chars) or \'q\' to exit: ";
                }
            }
        }
    }while (!valid);

    //-----WE KEEP ASKING WHILE THE INSERTION IS
    //CORRECT; THE FORMAT IS CORRECT AND IT IS NOT "q"


    proflist.push_back(new Professor (name, ident, this));
}



void VirtualCampus::deleteTeacher(unsigned index)
{
    if (index < proflist.size()){
        delete proflist[index];
        proflist.erase(proflist.begin()+index);
    }else {
        cerr<<"VirtualCampus::deleteTeacher(int); Invalid index\n";
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
    seminarMenu.run();

}



void VirtualCampus::addseminar()
{
    system("clear");
    bool valid;
    string id, name;
    Professor* Coord;
    unsigned day, month, year;
    unsigned seats;

    std::string buffer; //Auxiliar string to prevent buffer loops and incorrect insertions


    // ----ASKING FOR THE ID-----


    do {
        system("clear");
        valid = true;
        if (!cin.good()){
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout<<"Enter the identification (CCCIIII, C=Letter, I=Number) or \'q\' to cancel: \nSEM";

        if (!(std::cin>>std::ws>>buffer) || (!checkResId("SEM"+buffer) && buffer !="q")){
            valid = false;
        }else{

                for (auto it: seminalist){
                    if (it->getIdentification()=="SEM"+buffer){
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


    //---- ASKING FOR THE NAME OF THE SEMINAR-----

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do {
        system("clear");
        if (!cin.good()){
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }


        std::cout<<"Enter the new name or \'q\' to cancel: ";

    }while(!getline(cin, buffer, '\n') || !checkletters(buffer));

    if (buffer!="q"){
        name=buffer;
    }else{
        return;
    }



    //----- ASKING FOR THE MAXIMUM NUMBER OF SEATS----


    do {
        system("clear");
        if (!cin.good()){
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout<<"Enter the new value for the maximum number of seats or \'q\' to cancel:";
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
        std::cout<<"Enter the date (day month year) or \'q\' to cancel:";
        getline(std::cin, buffer, '\n');

        if (buffer=="q"){
            return;
        }

    }while(!(istringstream(buffer)>>day>>month>>year));




    //WE CREATE A SELECTOR TO SELECT THE TEACHER
    if (proflist.size()>0){
        Menu<Professor> CoordSelector(proflist, User::gimmethename());
        Coord=CoordSelector.run_selector();
        if (!Coord)
            return;


        // IF WE DIDN'T ABORT WE CREATE THE NEW SEMINAR

        seminalist.push_back(new Seminar(name, id, this, seats, Coord, Date (day, month, year)));
    }else{
        cout<<"Create a teacher first to be the coordinator, Seminar not created\n";
        cin.ignore(numeric_limits<char>::max(), '\n');
        cin.get();
    }


}



void VirtualCampus::deleteSeminar()
{
    Menu<Seminar> deleteSelector(seminalist, Resource::gimmetheid());
    Seminar *to_remove=deleteSelector.run_selector();
    if (to_remove){
        for (vector<Seminar*>::iterator it = seminalist.begin(); it!=seminalist.end(); it++){
            if ((*it)==to_remove){
                seminalist.erase(it);
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
        return; //IF "q" was inserted we abort
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

    }while(!getline(cin, buffer, '\n') || !checkletters(buffer));

    if (buffer!="q"){
        name=buffer;
    }else{
        return;
    }


    Menu<Degree> degree_selector(degreelist, Degree::gimme_the_name(), "Select a degree to select a student or q to skip");

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

    if (temp_student){

        Menu<Professor> professor_selector (professor_selector_options, "Select the teacher or \'q\' to leave it blank");

        temp_professor= professor_selector.run_selector();

        projectlist.push_back(new FDP(name, id, this, temp_student, temp_professor));

    }else{

        Menu<Professor> professor_selector (professor_selector_options, "You must select a teacher or \'q\' to cancel");

        temp_professor= professor_selector.run_selector();

        if (temp_professor){
            projectlist.push_back(new FDP(name, id, this, temp_student, temp_professor));
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
            }
        }
        delete to_remove;
    }
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











