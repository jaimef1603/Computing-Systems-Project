#include "Link_stu_res.h"
#include <iostream>
#include "Resource.h"
#include "Student.h"


Link_stu_res::Link_stu_res(Student *s, Resource *r)
    :Link_us_res (r)
{
    if(s!=nullptr){
        stuPtr=s;
    }else{
        std::cerr<<"Link_stu_res::Link_stu_res(Student*, Resource*); invalid student.\n";
        this->~Link_stu_res();
    }
}



Link_stu_res::Link_stu_res(const Link_stu_res& other)
    :Link_us_res (other)
{
    this->stuPtr=other.stuPtr;
}



Link_stu_res::~Link_stu_res()
{
    this->destroy();
}



Link_stu_res& Link_stu_res::operator= (const Link_stu_res &other)
{
    this->Link_us_res::operator=(other);
    return *this;
}



bool Link_stu_res::operator== (const Link_stu_res &other)
{
    return (resourcePtr==other.resourcePtr && stuPtr==other.stuPtr )? true:false;
}



int Link_stu_res::checkHealth()
{
    if(stuPtr==nullptr && resourcePtr==nullptr){
        return -2;
    }else if(stuPtr!=nullptr && resourcePtr!=nullptr){
        return 0;
    }else{
        return -1;
    }
}



Student& Link_stu_res::getStudent()
{
    return *stuPtr;
}



void Link_stu_res::setfinalMark(float value, Date when)
{
    final=Mark(value, when);
}



void Link_stu_res::setfinalMark(Mark value){
    final=Mark(value);
}



void Link_stu_res::setpartialMark(float value, Date when, int position)
{
        partial[position]=Mark(value, when);

}



void Link_stu_res::setpartialMark(Mark value, int position)
{
        partial[position]=value;

}



void Link_stu_res::setpartialMark(Mark value[])
{
    for(int i=0;i<4;i++){
        partial[i]=value[i];
    }
}


Mark& Link_stu_res::getfinalMark()
{
    return final;
}


Mark* Link_stu_res::getpartiaMark()
{
    return partial;
}



void Link_stu_res::connectStutoCourse()
{
    stuPtr->addCourse(this);
}



void Link_stu_res::connectStutoSeminar()
{
    stuPtr->addSeminar(this);
}



void Link_stu_res::connectStutoFDP()
{
    stuPtr->addFDP(this);
}



void Link_stu_res::connectResource()
{
    resourcePtr->addstudent(this);
}



void Link_stu_res::destroy()
{
    resourcePtr->removestudent(this);
    stuPtr->removeResource(this);
}



void Link_stu_res::showDetails()
{
    resourcePtr->showDetails();

    if (this->resourcePtr->getIdentification().find("SEM")==string::npos && this->resourcePtr->getIdentification().find("FDP")==string::npos){

        cout<<"GRADES:"<<endl
           <<"\tPartial evaluation:"<<endl;
        for (unsigned i=0; i<4; i++){
            cout<<"\t "<<i<<": ";
            if (partial[i].getvalue()==-1){
                cout<<"Not Graded"<<endl;
            }else{
                cout<<partial[i].getvalue()<<" Date: "<<partial[i].getdate_graded();
            }
        }
        cout<<"\tFinal: ";
        if(final.getvalue()==-1){
            cout<<"Not graded"<<endl;
        }else{
            cout<<final.getvalue()<<" Date: "<<final.getdate_graded()<<endl;

        }
    }

}



void Link_stu_res::grade()
{
    unsigned day, month, year;
    int value;
    char selection;

    do {
    system("clear");
    cout<<resourcePtr->getname()+" - grades of "+ stuPtr->getname()+ " ID: "+stuPtr->getidentifier()<<endl;
    cout<<"\t[1] Partial evaluation 1"<<endl
       <<"\t[2] Partial evaluation 2"<<endl
            <<"\t[3] Partial evaluation 3"<<endl
           <<"\t[4] Partial evaluation 4"<<endl
             <<"\t[5] Final evaluation"<<endl
            <<"\t'q' Exit"<<endl;
        if (!cin.good()){
            cin.clear();
            cin.ignore(numeric_limits<char>::max(), '\n');
        }
        cin>>selection;
    }while(((selection < '1' || selection> '5') && selection != 'q') || !cin.good());
    if (selection == 'q')
    {
        return;
    }


    do {
        system("clear");
        cout<<resourcePtr->getname()+" - grades of "+ stuPtr->getname()+ " ID: "+stuPtr->getidentifier()<<endl;
        cout<<"Enter the mark: ";
        if (!cin.good()){
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
        }
        cin>>value;
    }while(((value < 0 && value !=-1) || value> 10 ) || !cin.good());


       do{
           system("clear");
           cout<<resourcePtr->getname()+" - grades of "+ stuPtr->getname()+ " ID: "+stuPtr->getidentifier()<<endl;
           cout<<"Enter the date(day month year): ";
           if (!cin.good()){
               cin.clear();
               cin.ignore(numeric_limits<int>::max(), '\n');
           }
           cin>>day>>month>>year;
       }while(!cin.good());


    if ((selection - '0'-1) != 5){
        setpartialMark(value, Date(day, month, year), selection-'0'-1);
    }
    else{
        setfinalMark(value, Date(day, month, year));
    }

}

