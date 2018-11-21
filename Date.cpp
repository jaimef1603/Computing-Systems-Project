#include <iostream>
#include <stdio.h>
#include "Date.h"
#include <string>
using namespace std;

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
                    day=d;
                }else{
                    day=1;
                    cout<<"not correct date"<<endl;
                }
              break;
            case 4:
            case 6:
            case 9:
            case 11:
                if(d>=1 && d<=30){
                    day=d;
                 }else{
                    day=1;
                    cout<<"not correct date"<<endl;
                 }
              break;
            case 2:
                if((y%4==0 && y%100!=0) || y%400==0){
                    if(d>=1 && d<=29){
                        day =d;
                     }else{
                        day=1;
                        cout<<"not correct date"<<endl;
                     }
                }else{
                    if(d>=1 && d<=28){
                        day=d;
                     }else{
                        day=1;
                        cout<<"not correct date"<<endl;
                     }
                 }
              break;
            }
    }else{
        if (y<=0){
            year=1;
            cerr<<"Incorrect year, assigning to 1\n";
        }else{
            year=y;
        }
        if (m<=0 || m>=13){
            month=1;
            cerr<<"Incorrect month, assigning to 1\n";
        }else{
            month=m;
        }

    }



}



Date::Date(const Date &other){
    int d=other.day, m=other.month, y=other.year;
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
                    day=d;
                }else{
                    day=1;
                    cout<<"not correct date"<<endl;
                }
              break;
            case 4:
            case 6:
            case 9:
            case 11:
                if(d>=1 && d<=30){
                    day=d;
                 }else{
                    day=1;
                    cout<<"not correct date"<<endl;
                 }
              break;
            case 2:
                if((y%4==0 && y%100!=0) || y%400==0){
                    if(d>=1 && d<=29){
                        day =d;
                     }else{
                        day=1;
                        cout<<"not correct date"<<endl;
                     }
                }else{
                    if(d>=1 && d<=28){
                        day=d;
                     }else{
                        day=1;
                        cout<<"not correct date"<<endl;
                     }
                 }
              break;
            }
    }else{
        if (y<=0){
            year=1;
            cerr<<"Incorrect year, assigning to 1\n";
        }else{
            year=y;
        }
        if (m<=0 || m>=13){
            month=1;
            cerr<<"Incorrect month, assigning to 1\n";
        }else{
            month=m;
        }

    }


}


Date& Date::operator=(const Date &d){

    day=d.day;
    month=d.month;
    year=d.year;

    return *this;
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

    if(month!=0 && year!=0){

        switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if(d>=1 && d<=31){
                day=d;
            }else{
                cout<<"not correct date, setting day to 1"<<endl;
                day=1;
            }
          break;

        case 2:
            if((year%4==0 && year%100!=0) || year%400==0){
                if(d>=1 && d<=29){
                      day=d;
                }else{
                    cout<<"not correct date, setting day to 1"<<endl;
                    day=1;
                   }
           }else{
                if(d>=1 && d<=28){
                      day=d;
                 }else{
                    cout<<"not correct date, setting day to 1"<<endl;
                    day=1;
                   }
            }
          break;

        default:
            if(d>=1 && d<=30){
                day=d;
             }else{
                cout<<"not correct date, setting day to 1"<<endl;
                day=1;
             }
          break;
        }
    }else{
        day=d;
    }
}

void Date::setmonth(int m){

    if(day!=0 && year!=0){

        switch (m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if(day>=1 && day<=31){
                month=m;
            }else{
                cout<<"not correct date, setting month to 1"<<endl;
                month=1;
            }
          break;
        case 4:
        case 6:
        case 9:
        case 11:
            if(day>=1 && day<=30){
                month=m;
             }else{
                cout<<"not correct date, setting month to 1"<<endl;
                month=1;
             }
          break;
        case 2:
            if((year%4==0 && year%100!=0) || year%400==0){
                if(day>=1 && day<=29){
                    month=m;
                 }else{
                    cout<<"not correct date, setting month to 1"<<endl;
                    month=1;
                 }
            }else{
                if(day>=1 && day<=28){
                    month=m;
                 }else{
                    cout<<"not correct date, setting month to 1"<<endl;
                    month=1;
                 }
             }
          break;

        default:
            cout<<"not correct date, setting month to 1"<<endl;
            month=1;
            break;
        }
    }else{
         month=m;
    }
}
void Date::setyear(int y){

    if(day!=0 && month!=0){

        if (month==2 && day==29){
            if((y%4==0 && y%100!=0) || y%400==0){
                year=y;
            }else{
                cout<<"not correct date, setting year to 2018"<<endl;
                year=2018;
            }
        }
    }else{
        year=y;
    }
}
