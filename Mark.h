#ifndef MARK_H
#define MARK_H
#include <string>
#include <Date.h>
using namespace std;

class Mark
{
private:
    float value;
    Date date_graded;
public:
    Mark(float v = -1);
    Mark(float v, Date when);
    void setvalue(float v);
    float getvalue();
    void setdate_graded(Date when);
    void setdate_graded(int day, int month, int year);
    Date getdate_graded();
};


#endif // MARK_H
