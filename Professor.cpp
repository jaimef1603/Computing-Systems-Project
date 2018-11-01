#include "Professor.h"
#include <string>
Professor::Professor(){

}
Professor::Professor(string ident){
    identifier=ident;
}
string Professor::getidentifier(){
    return identifier;
}
void Professor::setidentifier(string ident){
    identifier=ident;
}
