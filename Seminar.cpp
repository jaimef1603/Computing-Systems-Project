#include "Seminar.h"
#include <iostream>



Seminar::Seminar(string id, string s, int seatsValue, Date when, Professor *spe, Professor *coord)
{
    setIdentification(id);
    setstatus(s);
    if (seatsValue >0){
        maxseats=seatsValue;
    }else{
        std::cerr<<"Seminar::Seminar(string, string, int, Date, User, User); seatsValue invalid, assigning seats to 1\n";
        maxseats=1;
    }
    freeseats=maxseats;
    students=new Link_stu_res* [maxseats];//students=new Link_us_res [maxseats];
    for (int i=0; i<maxseats; i++){
        students[i]=nullptr;
    }
    eventDate=when;
    setspeaker(spe);
    setcoordinator(coord);

}



Seminar::Seminar(string id, string s, int seatsValue, Professor *spe, Professor *coord)
{
    setIdentification(id);
    setstatus(s);
    if (seatsValue >0){
        maxseats=seatsValue;
    }else{
        std::cerr<<"Seminar::Seminar(string, string, int, User, User); seatsValue invalid, assigning seats to 1\n";
        maxseats=1;
    }
    freeseats=maxseats;
    students=new Link_stu_res* [maxseats]; //students=new Link_us_res [maxseats];
    for (int i=0; i<maxseats; i++){
        students[i]=nullptr;
    }
    setspeaker(spe);
    setcoordinator(coord);

}



int Seminar::getmaxseats()const
{
    return maxseats;
}



void Seminar::setmaxseats(int s)
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



void Seminar::setspeaker(Professor *spe)
{
    Link_prof_res *newLink=new Link_prof_res(spe, this);//Link_us_res *newLink=new Link_us_res(spe, this);
    if (newLink->checkHealth()==0){
        //if (!newLink->checkUserKind()){
        speaker=newLink;
        //}else{
        //delete newLink;
        //std::cerr<<"Seminar::setspeaker(User*); User passed is not valid for speaker. Only teachers can be speaker.\n";
        //}
    }else{
        std::cerr<<"Seminar::setspeaker(User*); failed to create a new link\n";
    }
}



Link_prof_res& Seminar::getspeaker()const
{
    return *speaker;
}



void Seminar::setcoordinator(Professor *coord)
{
    Link_prof_res *newLink=new Link_prof_res(coord, this);
    if (newLink->checkHealth()==0){
        //if (!newLink->checkUserKind()){
        coordinator=newLink;
        //}else{
        //delete newLink;
        //std::cerr<<"Seminar::setcoordinator(User*); User passed is not valid for coordnator. Only teachers can be coordinator.\n";
        //}
    }else{
        std::cerr<<"Seminar::setcoordinator(User*); failed to create a new link\n";
    }
}



Link_prof_res& Seminar::getcoordinator()const
{
    return *coordinator;
}



void Seminar::addteacher(Link_prof_res *newteacher)
{

}




void Seminar::addstudent(Link_stu_res *newstudent)
{
    bool flag = false;
    if (freeseats>0){
        for (int i=0; i<maxseats; i++){
            if (students[i]==nullptr){
                students[i]=newstudent;
                flag = true;
                freeseats-=1;
                break;
            }
        }
    }
    if (!flag){
        cerr<<"Seminar::addstudent(Link_us_res*); Student was not added.\n";
    }
}


void Seminar::removestudent(Link_stu_res *link){
    int i;
    bool flag = false;
    for (i=0; i<maxseats-1; i++){
        if (students[i]==link){
            flag = true;
            for(;i<maxseats; i++){
                students[i]=students[i+1];
            }
            freeseats+=1;
            break;
        }

        if (!flag){
            cerr<<"Seminar::removestudent(Link_us_res*); No student removed.\n";
        }
    }

}
