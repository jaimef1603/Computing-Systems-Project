#include "Professor.h"
#include <string>
Professor::Professor(): identifier("0"), coursePtrlist(), fdpPtrlist(), seminarPtrlist(){

}
Professor::Professor(string ident):coursePtrlist(), fdpPtrlist(), seminarPtrlist(){
    identifier=ident;
}
string Professor::getidentifier(){
    return identifier;
}
void Professor::setidentifier(string ident){
    identifier=ident;
}
void Professor::menu(){

}
