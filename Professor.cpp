#include "Professor.h"
#include <string>

Professor::Professor(): identifier("0"), courselist(), fdplist(), seminarlist(){

}

Professor::Professor(string ident):courselist(), fdplist(), seminarlist(){
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
