#include "Date.h"
#include <string>
using namespace std;

Date::Date(){

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
