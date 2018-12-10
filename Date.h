#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date
{
private:
    unsigned day;
    unsigned month;
    unsigned year;
public:
    Date(unsigned d=1, unsigned m=1, unsigned y=1);
    Date(const Date &other);
    Date& operator = (const Date &d);
    unsigned getday();
    void setday(unsigned d);
    unsigned getmonth();
    void setmonth(unsigned m);
    unsigned getyear();
    void setyear(unsigned y);
    friend std::ostream& operator<<(std::ostream& os, const Date & dat);
    friend std::ostream& operator<<(std::ostream& os, const Date && dat);
};

#endif // DATE_H
