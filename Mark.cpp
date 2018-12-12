#include "Mark.h"
#include <iostream>

Mark::Mark(float v): date_graded()
{
    if ((v>=0 && v<=10) || v==-1){ // revisar
        value = v;
    }else {
        std::cerr<<"Mark::Mark(float); Value not valid, assigning -1\n";
        value=-1;
    }

}



Mark::Mark(float v, Date when): date_graded(when)
{
    if ((v>=0 && v<=10) || v==-1){ // revisar
        value = v;
    }else {
        std::cerr<<"Mark::Mark(float); Value not valid, assigning -1\n";
        value=-1;
    }

}



float Mark::getvalue()
{
    return value;
}



void Mark::setvalue(float v)
{
    if ((v>=0 && v<=10) || v==-1){ // revisar
        value = v;
    }else {
        std::cerr<<"Mark::setvalue(float); Value not valid, assigning -1\n";
    }
}



void Mark::setdate_graded(Date when)
{
    date_graded=when;
}



void Mark::setdate_graded(int day, int month, int year)
{
    date_graded.setday(day);
    date_graded.setmonth(month);
    date_graded.setyear(year);
}



Date Mark::getdate_graded()
{
    return date_graded;
}



// ------- FILE HANDLING FUNCTIONS-------



//ofstream & operator<< (ofstream& ofs, Mark _mark)
//{

//    ofs.write(reinterpret_cast<char*>(&(day)), sizeof (unsigned));
//    ofs.write(reinterpret_cast<char*>(&(month)), sizeof (unsigned));
//    ofs.write(reinterpret_cast<char*>(&(year)), sizeof (unsigned));
//    return ofs;
//}


//ifstream & operator<< (ifstream& ifs, Mark _mark)
//{

//    ifs.read(reinterpret_cast<char*>(&(day)), sizeof (unsigned));
//    ifs.read(reinterpret_cast<char*>(&(month)), sizeof (unsigned));
//    ifs.read(reinterpret_cast<char*>(&(year)), sizeof (unsigned));
//    return ifs;
//}

