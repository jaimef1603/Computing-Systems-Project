#include <iostream>
#include <stdio.h>
#include "Date.h"
#include <string>
using namespace std;

Date::Date(){

}
Date::Date(int d, int m, int y){
    if((m>0 && m<13) && y>0){

        switch(m){
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if(d>=1 && d<=31){
                    cout<<"correct date"<<endl;
                }else{
                    cout<<"not correct date"<<endl;
                }
              break;
            case 4:
            case 6:
            case 9:
            case 11:
                if(d>=1 && d<=30){
                    cout<<"correct date"<<endl;
                 }else{
                    cout<<"not correct date"<<endl;
                 }
              break;
            case 2:
                if((y%4==0 && y%100!=0) || y%400==0){
                    if(d>=1 && d<=29){
                        cout<<"correct date"<<endl;
                     }else{
                        cout<<"not correct date"<<endl;
                     }
                }else{
                    if(d>=1 && d<=28){
                        cout<<"correct date"<<endl;
                     }else{
                        cout<<"not correct date"<<endl;
                     }
                 }
              break;
            }
       }

}
int Date::getday(){
    return day;
}
int Date::getmonth(){
    return month;
}
int Date::getyear(){
    return year;
}
void Date::setday(int d){
    day=d;
}
void Date::setmonth(int m){
    month=m;
}
void Date::setyear(int y){
    year=y;
}
