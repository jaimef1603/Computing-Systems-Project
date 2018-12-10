#include <iostream>
#include <stdio.h>
#include "Date.h"
#include <string>
using namespace std;

Date::Date(unsigned d, unsigned m, unsigned y)
{
    if((m>0 && m<13) && y>1900){

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
                    cerr<<"Not correct date, setting day to 1"<<endl;
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
                    cerr<<"Not correct date, setting day to 1"<<endl;
                 }
              break;
            case 2:
                if((y%4==0 && y%100!=0) || y%400==0){
                    if(d>=1 && d<=29){
                        day =d;
                     }else{
                        day=1;
                        cerr<<"Not correct date, setting day to 1"<<endl;
                     }
                }else{
                    if(d>=1 && d<=28){
                        day=d;
                     }else{
                        day=1;
                        cerr<<"Not correct date, setting day to 1"<<endl;
                     }
                 }
              break;
            }
    }else{
        if (y<=1900){
            year=1901;
            cerr<<"Not correct date, setting year to 2018"<<endl;
        }else{
            year=y;
        }
        if (m<=0 || m>=13){
            month=1;
            day = 1;
            cerr<<"Not correct date, setting month and day to 1"<<endl;
        }else{
            month=m;
        }

    }

}



Date::Date(const Date &other)
{
    unsigned d=other.day, m=other.month, y=other.year;
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
                    cerr<<"Not correct date, setting day to 1"<<endl;
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
                    cerr<<"Not correct date, setting day to 1"<<endl;
                 }
              break;
            case 2:
                if((y%4==0 && y%100!=0) || y%400==0){
                    if(d>=1 && d<=29){
                        day =d;
                     }else{
                        day=1;
                        cerr<<"Not correct date, setting day to 1"<<endl;
                     }
                }else{
                    if(d>=1 && d<=28){
                        day=d;
                     }else{
                        day=1;
                        cerr<<"Not correct date, setting day to 1"<<endl;
                     }
                 }
              break;
            }
    }else{
        if (y<=0){
            year=2018;
            cerr<<"Not correct date, setting year to 2018"<<endl;
        }else{
            year=y;
        }
        if (m<=0 || m>=13){
            month=1;
            cerr<<"Not correct date, setting month to 1"<<endl;
        }else{
            month=m;
        }

    }

}


Date& Date::operator=(const Date &d)
{

    day=d.day;
    month=d.month;
    year=d.year;

    return *this;
}



unsigned Date::getday()
{
    return day;
}



unsigned Date::getmonth()
{
    return month;
}



unsigned Date::getyear()
{
    return year;
}



void Date::setday(unsigned d)
{
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
                cout<<"Not correct date, setting day to 1"<<endl;
                day=1;
            }
          break;

        case 2:
            if((year%4==0 && year%100!=0) || year%400==0){
                if(d>=1 && d<=29){
                      day=d;
                }else{
                    cout<<"Not correct date, setting day to 1"<<endl;
                    day=1;
                   }
           }else{
                if(d>=1 && d<=28){
                      day=d;
                 }else{
                    cout<<"Not correct date, setting day to 1"<<endl;
                    day=1;
                   }
            }
          break;

        default:
            if(d>=1 && d<=30){
                day=d;
             }else{
                cout<<"Not correct date, setting day to 1"<<endl;
                day=1;
             }
          break;
        }
    }else{
        day=d;
    }
}



void Date::setmonth(unsigned m)
{
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
                cout<<"Not correct date, setting month to 1"<<endl;
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
                cout<<"Not correct date, setting month to 1"<<endl;
                month=1;
             }
          break;
        case 2:
            if((year%4==0 && year%100!=0) || year%400==0){
                if(day>=1 && day<=29){
                    month=m;
                 }else{
                    cout<<"Not correct date, setting month to 1"<<endl;
                    month=1;
                 }
            }else{
                if(day>=1 && day<=28){
                    month=m;
                 }else{
                    cout<<"Not correct date, setting month to 1"<<endl;
                    month=1;
                 }
             }
          break;

        default:
            cout<<"Not correct date, setting month to 1"<<endl;
            month=1;
            break;
        }
    }else{
         month=m;
    }
}



void Date::setyear(unsigned y)
{
    if(day!=0 && month!=0){

        if (month==2 && day==29){
            if((y%4==0 && y%100!=0) || y%400==0){
                year=y;
            }else{
                cout<<"Not correct date, setting year to 2018"<<endl;
                year=2018;
            }
        }
    }else{
        year=y;
    }
}



std::ostream& operator<<(std::ostream& os, const Date & dat)
{
    os<<dat.day<<"/"<<dat.month<<"/"<<dat.year;
    return os;
}



std::ostream& operator<<(std::ostream& os, const Date && dat)
{
    os<<dat.day<<"/"<<dat.month<<"/"<<dat.year;
    return os;
}

