#include "Administrator.h"

Administrator::Administrator():Professor()
{

    AdminPtr=nullptr;
    profesorPtr=nullptr;
    degreePtr=nullptr;
    seminarPtr=nullptr;
    fdpPtr=nullptr;
}

Administrator::Administrator(string ident, const Administrator &admin):Professor(ident){

    AdminPtr=admin.AdminPtr;
    profesorPtr=admin.profesorPtr;
    degreePtr=admin.degreePtr;
    seminarPtr=admin.seminarPtr;
    fdpPtr=admin.fdpPtr;

}
