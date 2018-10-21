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
    Date();
    int getday();
    void setday(int d);
    int getmonth();
    void setmonth(int m);
    int getyear();
    void setyear(int y);
};

#endif // DATE_H
