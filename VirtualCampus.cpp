#include "VirtualCampus.h"

VirtualCampus::VirtualCampus()
{
    admin_number=0;
    admins=nullptr;
    prof_number=0;
    proflist=nullptr;
    degree_number=0;
    degreelist=nullptr;
    seminar_number=0;
    seminalist=nullptr;
    currentuser=new Administrator("aaaaaa", this);
    fdp_number=0;
    projectlist=nullptr;


}



VirtualCampus::~VirtualCampus()
{
    if (degreelist!=nullptr){
        delete [] degreelist;
    }
    if (seminalist!=nullptr){
        delete [] seminalist;
    }
    if (projectlist!=nullptr){
        delete [] projectlist;
    }
    if (currentuser!=nullptr){
        delete degreelist;
    }
}



void VirtualCampus::run()
{

    currentuser->menu();
    system("clear");

    if (degreelist!=nullptr){
        cout<<degreelist[0].getname();
        degreelist[0].showcourses();
        cout<<endl;
    }
    if (projectlist!=nullptr){
        cout<<projectlist[0].getIdentification()<<endl;
    }
    if (seminalist!=nullptr){
        cout<<seminalist[0].getIdentification()<<endl;
    }

    getchar();
}



void VirtualCampus::addDegree()
{
    string name;
    cout<<"Enter the name of the degree: ";
    cin>>ws>>name;
    Degree *temp;
    if (degreelist==nullptr){
        degreelist = new Degree[1];
        degreelist[0] = Degree(name);
        degree_number=1;
        std::cerr<<"Degree added\n";
        getchar();
    }else{
        if (degree_number>0){
            temp=new Degree [degree_number];
            for(int i=0; i<degree_number; i++){
                temp[i]=degreelist[i];
            }
            delete [] degreelist;
            degreelist = new Degree[degree_number+1];
            for(int i=0; i<degree_number; i++){
                degreelist[i]=temp[i];
            }
            delete [] temp;
            degreelist[degree_number] = Degree(name);
            degree_number+=1;
        }else{
            cerr<<"VirtualCampus::addDegree(); Invalid size for degree_number.\n"<<endl;
        }
    }
}



void VirtualCampus::addFDP()
{

    string id;
    //string namedegree, studentid;
    //int degreeid;
    //Student *stu;
    FDP *temp;
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

    if (projectlist==nullptr){
        projectlist = new FDP[1];
        projectlist[0]= FDP(id);
        fdp_number=1;
    }else{
        if (fdp_number>0){
            temp=new FDP [fdp_number];
            for(int i=0; i<fdp_number; i++){
                temp[i]=projectlist[i];
            }
            delete [] projectlist;
            projectlist = new FDP[fdp_number+1];
            for(int i=0; i<fdp_number; i++){
                projectlist[i]=temp[i];
            }
            projectlist[fdp_number]= FDP(id);
            delete [] temp;
            fdp_number+=1;
        }else{
            cerr<<"VirtualCampus::addDegree(); Invalid size for degree_number.\n"<<endl;
        }
    }

}



void VirtualCampus::addseminar()
{

    string id;
    cout<<"Enter the name of the seminar: ";
    cin>>ws>>id;
    Seminar *temp;
    if (seminalist==nullptr){
        seminalist = new Seminar[1];
        seminalist[0]=Seminar(id);
        seminar_number=1;
    }else{
        if (seminar_number>0){
            temp=new Seminar [seminar_number];
            for(int i=0; i<seminar_number; i++){
                temp[i]=seminalist[i];
            }
            delete [] seminalist;
            seminalist = new Seminar[seminar_number+1];
            for(int i=0; i<seminar_number; i++){
                seminalist[i]=temp[i];
            }
            delete [] temp;
            seminalist[seminar_number]=Seminar(id);
            seminar_number+=1;
        }else{
            cerr<<"VirtualCampus::addseminar(); Invalid size for seminar_number.\n"<<endl;
        }
    }

}



void VirtualCampus::addCourse()
{
    string degreeid;
    cout<<"Enter the name of the degree the course will belong to: ";
    cin>>ws>>degreeid;
    for (int i=0; i<degree_number; i++){
        if (degreelist[i].getname()==degreeid){
            degreelist[i].addCourse();
            break;
        }

    }
}
