#include "Administrator.h"

Administrator::Administrator():Professor()
{

}

Administrator::Administrator(string ident, const Administrator &admin):Professor(ident){

    AdminPtr=admin.AdminPtr;
    profesorPtr=admin.profesorPtr;
    studentPtr=admin.studentPtr;
    coursePtr=admin.coursePtr;
    seminarPtr=admin.seminarPtr;
    fdpPtr=admin.fdpPtr;

}
