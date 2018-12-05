#include "VirtualCampus.h"
#include "Utilities.h"
#include <sstream>
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



int VirtualCampus::run()
{
    int r;
    r=currentuser->menu();
    system("clear");
    fflush(stdout);

    getchar();
    return r;
}



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
            (*(getDegrees().end()-1))->showdetails();
            cin.ignore(1, '\n');
            getchar();
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
            cout<<"Enter a valid number(1-5)\n"<<endl;
            cin>>selection;
            break;

        }
    }while(true);

}




void VirtualCampus::addDegree()
{
    system("clear");
    string name, id;
    cout<<"Enter the name of the degree (letters a-z, A-Z) or \"cancel\" to exit : ";
    do{
        cin>>ws>>name;
        if (name =="cancel"){
            return;
        }
    }while(!checkletters(name));
    do{
        system("clear");
        cout<<"Name: "<<name<<endl;
        cout<<"Enter the three letter identification or write \"cancel\" to exit: ";
        cin>>ws>>id;
        if (id=="cancel"){
            return;
        }
    }while(!checkletters(id) || id.length()!=3);
    UCaseWord(id);
    degreelist.push_back(new Degree(name, id.c_str(), this));

}



void VirtualCampus::deleteDegree(unsigned index){


    delete degreelist[index];
    degreelist.erase(degreelist.begin()+index);


}



int VirtualCampus::findDegree(string identification)
{


    for (unsigned i=0; i<degreelist.size(); i++ ){
        if (degreelist[i]->getid()==identification){
            return int(i);
        }
    }
    return -1;



}



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
            cout<<"Enter the id of the teacher you want to show details.\n";

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
                    cout<<"Enter the id of the teacher you want to show details.\n";
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
            cout<<"Enter the id of the teacher you want to show details.\n";

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
                    cout<<"Enter the id of the teacher you want to show details.\n";
                }
            }while(teach==-1);
            system("clear");
            if (teach!=-1){
                proflist[unsigned(teach)]->showdetails();
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
                    cout<<"Enter the id of the teacher you want to show details.\n";
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
    string id, name;
    cout<<"Enter the ID of the teacher: ";
    cin>>ws>>id;
    cout<<"Enter the name of the teacher: ";
    cin>>ws>>name;
    proflist.push_back(new Professor (name, id, this));
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



int VirtualCampus::findTeacher(string identification)
{


    for (unsigned i=0; i<proflist.size(); i++ ){
        if (proflist[i]->getidentifier()==identification){
            return int(i);
        }
    }
    return -1;



}



vector<Seminar*> VirtualCampus::getSeminars()
{
    return seminalist;
}






vector <Degree*> VirtualCampus::getDegrees()
{
    return degreelist;
}



vector <Professor*> VirtualCampus::getTeachers()
{
    return proflist;
}





void VirtualCampus::showAllDeg()
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



void VirtualCampus::showAllTeach()
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



void VirtualCampus::showAllSeminars()
{

    for(unsigned i=0;i<seminalist.size();i++){
        cout<<i+1<<": "<<endl;
        cout<<"   "<<seminalist[i]->getIdentification();
    }

}




void VirtualCampus::addFDP()
{
    system("clear");
    string id, name;
    //string namedegree, studentid;
    //int degreeid;
    //Student *stu;
    //    FDP *temp;
    do{
    cout<<"Enter the id of the FDP: ";
    cin>>ws>>id;
    }while(!checkletters(id));
    do{
        cout<<"Enter the name of the FDP: ";
        cin>>ws>>name;
    }while(!checkletters(name));



    projectlist.push_back(new FDP(name, id));




}



void VirtualCampus::editFDP()
{
    system("clear");
    unsigned selection;
    string newname;
    char option;

    cout<<"Select the FDP you want to edit (1-"<<projectlist.size()<<")"<<endl;
    for (unsigned i=0; i<projectlist.size(); i++){
        cout<<i+1<<": "<<projectlist[i]->getIdentification()<<endl;
    }

    cin>>selection;
    system("clear");
    cout<<"1: Edit name 2:Edit ID 3: Back\n";
    cin>>ws>>option;
    switch (option) {
    case '1':{
        string newname;
        bool valid=false;
        system("clear");
        cout<<"Enter the new name (letters a-z, A-Z) or \"cancel\" to exit\n"<<endl;
        do {
            cin>>ws>>newname;
            if (newname=="cancel"){
                break;
            }
            if (!(valid=checkletters(newname))){
                cout<<"Enter a valid name or \"cancel\" to exit\n"<<endl;
            }
        }while (!valid);
        if (valid){
            projectlist[selection-1]->setname(newname);
        }
        break;
    }
    case '2':{
        string newId;
        bool valid=false;
        system("clear");
        cout<<"Enter the new ID CCCIIII (C=char, I=number) or \"cancel\" to exit\n"<<endl;
        do {
            cin>>ws>>newId;
            if (newId=="cancel"){
                break;
            }
            if (!(valid=checkResId(newId))){
                cout<<"Enter a valid ID CCCIIII (C=char, I=number) or \"cancel\" to exit\n"<<endl;
            }
        }while (!valid);
        if (valid){
            projectlist[selection-1]->setIdentification(newId);
        }
        break;
    }
    case '3': return;
    default:
        cout<<"Enter a valid number(1-3).\n\tPress any key to retry."<<endl;
        getchar();
        break;
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



void VirtualCampus::addseminar()
{
    system("clear");
    string id, name;
    string idCoord;
    int day, month, year;
    int coord=-1;
    unsigned seats;

    do{
        cout<<"Enter the identification of the seminar or \"cancel\" to exit: SEM";
        cin>>ws>>id;
        if(id=="cancel"){
            return;
        }
        id="SEM"+id;
    }while(!checkResId(id));

    do{
        cout<<"Enter the name of the seminar or \"cancel\" to exit: ";
        cin>>ws>>name;
        if(name=="cancel"){
            return;
        }
    }while(!checkletters(name));

    system("clear");

    //do{
        cout<<"Enter the maximum number of seats: ";
        cin>>seats;
    //}while(seats=0);
    cout<<"Enter values for day month and year separated by spaces: ";
    cin>>day>>month>>year;
    cout<<"Enter the id of the coordinator or \"cancel\" to exit: ";

    do {
        cin>>ws>>idCoord;
        if (idCoord=="cancel"){
            return;
        }else{
            coord=findTeacher(idCoord);
        }
        if(coord==-1){
            system("clear");
            cout<<"Invalid ID\n";
            cout<<"Enter the id of the coordinator \"cancel\" to exit:\n";
        }
    }while(coord==-1);


    seminalist.push_back(new Seminar(name, id, seats, proflist[unsigned(coord)], Date (day, month, year)));


}



//void VirtualCampus::editseminar(){

//    system("clear");
//    int seminar, field, newseats, day, month, year;
//    string newid;

//    do{
//        cout<<"Select the seminar you want to edit (1-"<<seminar_number+1<<")"<<endl;
//        for (int i=0; i<seminar_number; i++){
//            cout<<i+1<<": "<<seminalist[i].getIdentification()<<endl;
//        }
//        cin>>seminar;
//        system("clear");
//        cout<<"Select the field you want to edit (1-3)\n1: ID\n2: Maximum seats\n3: Date\n4: Back"<<endl;
//        cin>>field;
//        system("clear");
//        switch (field) {
//        case 1:
//            cout<<"Enter the new id: ";
//            cin>>newid;
//            seminalist[seminar-1].setIdentification(newid);
//            break;
//        case 2:
//            cout<<"Enter the new value for maximum seats: ";
//            cin>>newseats;
//            seminalist[seminar-1].setmaxseats(newseats);
//            break;
//        case 3:
//            cout<<"Enter values for day month and year separated by spaces: ";
//            cin>>day>>month>>year;
//            seminalist[seminar-1].setdate(Date(day,month,year));
//            break;
//        case 4:
//            return;
//        default:
//            cout<<"Enter a valid number(1-4).\n\tPress any key to retry."<<endl;
//            getchar();
//            break;
//        }
//    }while(true);
//}



int VirtualCampus::findSeminar(string identification)
{
    for (unsigned i=0; i<seminalist.size(); i++){
        if (identification==seminalist[i]->getIdentification()){
            return int(i);
        }
    }

    return -1;
}
