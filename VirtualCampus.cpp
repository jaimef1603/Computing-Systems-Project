#include "VirtualCampus.h"
#include "Utilities.h"
VirtualCampus::VirtualCampus()
{

    currentuser=new Administrator("aaaaaa", this);


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
    //    if (degreelist!=nullptr){
    //        cout<<"DEGREES & COURSES"<<endl;
    //        for(int i=0; i<degree_number; i++){
    //            cout<<degreelist[i].getname();
    //            degreelist[i].showcourses();
    //            cout<<endl;
    //        }
    //    }
    //    if (projectlist!=nullptr){
    //        cout<<"FDP's"<<endl;
    //        for(int i=0; i<fdp_number; i++){
    //            cout<<projectlist[i].getIdentification()<<endl;
    //        }
    //    }
    //    if (seminalist!=nullptr){
    //        cout<<"Seminars"<<endl;
    //        for(int i=0; i<seminar_number; i++){
    //            cout<<i+1<<": "<<seminalist[i].getIdentification()<<endl;
    //            cout<<"Seats: "<<seminalist[i].getmaxseats();
    //            //cout<<"\tDate: "<<seminalist[i].getdate();
    //        }
    //    }

    getchar();
    return r;
}





void VirtualCampus::addTeacher()
{
    system("clear");
    string id;
    cout<<"Enter the ID of the teacher: ";
    cin>>ws>>id;

    proflist.push_back(new Professor (id, this));


    //    if (proflist==nullptr){
    //        proflist = new Professor[1];
    //        proflist[0] = Professor(id, this);
    //        prof_number=1;
    //        std::cerr<<"Teacher added\n";
    //        getchar();
    //    }else{
    //        if (proflist!=nullptr){
    //            temp=new Professor [prof_number];
    //            for(int i=0; i<prof_number; i++){
    //                temp[i]=proflist[i];
    //            }
    //            delete [] proflist;
    //            proflist = new Professor[prof_number+1];
    //            for(int i=0; i<prof_number; i++){
    //                proflist[i]=temp[i];
    //            }
    //            delete [] temp;
    //            proflist[prof_number] = Professor(id, this);
    //            prof_number+=1;
    //            std::cerr<<"Teacher added\n";
    //        }else{
    //            cerr<<"VirtualCampus::addTeacher(); Invalid size for prof_number.\n"<<endl;
    //        }
    //    }
}



void VirtualCampus::deleteTeacher(unsigned index)
{
    if (index < proflist.size()){
        delete proflist[index];
        proflist.erase(proflist.begin()+index);
    }else {
        cerr<<"VirtualCampus::deleteTeacher(int); Invalid index\n";
    }



    //    Professor *temp = new Professor [prof_number-1];
    //    int j=0;

    //    for (int i = 0; i<prof_number; i++){
    //        if (i != index){
    //            temp[j]=proflist[i];
    //            j++;
    //        }
    //    }
    //    prof_number -=1;
    //    delete [] proflist;
    //    proflist = new Professor [prof_number];
    //    for (int i=0; i<prof_number; i++){
    //        proflist[i]=temp[i];
    //    }
    //    delete [] temp;
}



int VirtualCampus::findTeacher(string identification)
{


    for (unsigned i=0; i<proflist.size(); i++ ){
        if (proflist[i]->getidentifier()==identification){
            return int(i);
        }
    }
    return -1;


    //    if(proflist!=nullptr){
    //        for (int i=0; i<prof_number; i++){
    //            if (identification==proflist[i].getidentifier()){
    //                return i;
    //            }
    //        }
    //    }
    //    return -1;

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
        if (id=="cancel"){
            return;
        }
        cin>>ws>>id;
    }while(!checkletters(id) || id.length()!=3);
    UCaseWord(id);
    degreelist.push_back(new Degree(name, id.c_str(), this));



    //    Degree *temp;

    //        if (degreelist==nullptr){
    //            degreelist = new Degree[1];
    //            degreelist[0] = Degree(name, id.c_str(),  this);
    //            degree_number=1;
    //            std::cerr<<"Degree added\n";
    //            getchar();
    //        }else{
    //            if (degree_number>0){
    //                temp=new Degree [degree_number];
    //                for(int i=0; i<degree_number; i++){
    //                    temp[i]=degreelist[i];
    //                }
    //                delete [] degreelist;
    //                degreelist = new Degree[degree_number+1];
    //                for(int i=0; i<degree_number; i++){
    //                    degreelist[i]=temp[i];
    //                }
    //                delete [] temp;
    //                degreelist[degree_number] = Degree(name, id.c_str(), this);
    //                degree_number+=1;
    //            }else{
    //                cerr<<"VirtualCampus::addDegree(); Invalid size for degree_number.\n"<<endl;
    //            }
    //        }


}



void VirtualCampus::deleteDegree(unsigned index){


    delete degreelist[index];
    degreelist.erase(degreelist.begin()+index);



    //    Degree *temp = new Degree [degree_number-1];
    //    int j=0;

    //    for (int i = 0; i<degree_number; i++){
    //        if (i != index){
    //            temp[j]=degreelist[i];
    //            j++;
    //        }
    //    }
    //    degree_number -=1;
    //    delete [] degreelist;
    //    degreelist = new Degree [degree_number];
    //    for (int i=0; i<degree_number; i++){
    //        degreelist[i]=temp[i];
    //    }
    //    delete [] temp;
}



int VirtualCampus::findDegree(string identification)
{


    for (unsigned i=0; i<degreelist.size(); i++ ){
        if (degreelist[i]->getid()==identification){
            return int(i);
        }
    }
    return -1;


    //    if(degreelist!=nullptr){
    //        for (int i=0; i<degree_number; i++){
    //            if (identification.c_str()==degreelist[i].getid()){
    //                return i;
    //            }
    //        }
    //    }
    //    return -1;
}



void VirtualCampus::showAllDeg()
{
    if (degreelist.size()>0){
        cout<<"DEGREES:\n";
        for(unsigned i=0;i<degreelist.size();i++){

            cout<<i+1<<": "<<degreelist[i]->getname()<<endl;
        }
    }
}



void VirtualCampus::showAllTeach()
{

    for(unsigned i=0;i<proflist.size();i++){

        cout<<i+1<<": "<<proflist[i]->getidentifier()<<endl;
    }


    //    for(int i=0;i<prof_number;i++){

    //        cout<<i+1<<": "<<proflist[i].getidentifier()<<endl;
    //    }
}



void VirtualCampus::showAllSeminars()
{

    for(unsigned i=0;i<seminalist.size();i++){

        cout<<i+1<<": "<<seminalist[i]->getIdentification()<<endl;
    }

    //    for(int i=0;i<seminar_number;i++){

    //        cout<<i+1<<": "<<seminalist[i].getIdentification()<<endl;
    //    }
}




void VirtualCampus::addFDP()
{
    system("clear");
    string id;
    //string namedegree, studentid;
    //int degreeid;
    //Student *stu;
    //    FDP *temp;
    cout<<"Enter the id of the FDP: ";
    cin>>ws>>id;

    //    cout<<"What degree does the student belong to? enter the name of the degree.\n";
    //    cin>>ws>>namedegree;
    //    for (int i=0; i<degree_number; i++){
    //        if (degreelist[i].getname()==namedegree){
    //            degreelist[i].showstudents();
    //            degreeid = i;
    //            break;
    //        }
    //    }
    //    cout<<"Enter the id of the student."<<endl;
    //   stu = degreelist[degreeid].searchStudentbyid(studentid);


    projectlist.push_back(new FDP(id));


    //    if (projectlist==nullptr){
    //        projectlist = new FDP[1];
    //        projectlist[0]= FDP(id);
    //        fdp_number=1;
    //    }else{
    //        if (fdp_number>0){
    //            temp=new FDP [fdp_number];
    //            for(int i=0; i<fdp_number; i++){
    //                temp[i]=projectlist[i];
    //            }
    //            delete [] projectlist;
    //            projectlist = new FDP[fdp_number+1];
    //            for(int i=0; i<fdp_number; i++){
    //                projectlist[i]=temp[i];
    //            }
    //            projectlist[fdp_number]= FDP(id);
    //            delete [] temp;
    //            fdp_number+=1;
    //        }else{
    //            cerr<<"VirtualCampus::addDegree(); Invalid size for degree_number.\n"<<endl;
    //        }
    //    }

}



void VirtualCampus::editFDP()
{
    system("clear");
    unsigned selection;
    string newname;
    cout<<"Select the FDP you want to edit (1-"<<projectlist.size()<<")"<<endl;
    for (unsigned i=0; i<projectlist.size(); i++){
        cout<<i+1<<": "<<projectlist[i]->getIdentification()<<endl;
    }
    cin>>selection;
    system("clear");
    cout<<"Enter the new id"<<endl;
    cin>>ws>>newname;
    projectlist[selection-1]->setIdentification(newname);
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
    string id;
    cout<<"Enter the name of the seminar: ";
    cin>>ws>>id;

    seminalist.push_back(new Seminar(id));

    //    Seminar *temp;
    //    if (seminalist==nullptr){
    //        seminalist = new Seminar[1];
    //        seminalist[0]=Seminar(id);
    //        seminar_number=1;
    //    }else{
    //        if (seminar_number>0){
    //            temp=new Seminar [seminar_number];
    //            for(int i=0; i<seminar_number; i++){
    //                temp[i]=seminalist[i];
    //            }
    //            delete [] seminalist;
    //            seminalist = new Seminar[seminar_number+1];
    //            for(int i=0; i<seminar_number; i++){
    //                seminalist[i]=temp[i];
    //            }
    //            delete [] temp;
    //            seminalist[seminar_number]=Seminar(id);
    //            seminar_number+=1;
    //        }else{
    //            cerr<<"VirtualCampus::addseminar(); Invalid size for seminar_number.\n"<<endl;
    //        }
    //    }

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
