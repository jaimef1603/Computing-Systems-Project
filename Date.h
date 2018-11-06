#ifndef DATE_H
#define DATE_H
using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;
public:
    Date(int d=1, int m=1, int y=1);
    Date(Date &other);
    Date& operator = (const Date &d);
    int getday();
    void setday(int d);
    int getmonth();
    void setmonth(int m);
    int getyear();
    void setyear(int y);
};

#endif // DATE_H
