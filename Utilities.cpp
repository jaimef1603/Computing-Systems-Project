#include "Utilities.h"
#include <cstring>
using namespace std;

bool checkletters (const char str[]){

    for (int i=0; i<static_cast<int>(strlen(str)); i++){
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == ' '))){
            return false;
        }
    }
    return true;
}


bool checkletters (const string str){

    char *aux = new char [str.size()];
    strcpy(aux, str.c_str());
    for (int i=0; i<static_cast<int>(str.length()); i++){
        if (!((aux[i] >= 'a' && aux[i] <= 'z') || (aux[i] >= 'A' && aux[i] <= 'Z') || (aux[i] == ' '))){
            delete [] aux;
            return false;
        }
    }
    delete [] aux;
    return true;

}

void cleanWord (char str[]){

    for (int i=static_cast<int>(strlen(str)); i>1; i--){
        if (str[strlen(str)]==' ' && strlen(str)>1){
            str[strlen(str)]='\0';

        }
    }
    if (str[0]!=' '){
        str[0] = static_cast<char>(toupper(str[0]));
        for (int i=static_cast<int>(strlen(str)); i>0; i--){
            str[i]=static_cast<char>(tolower(str[i]));
        }
    }
}

void cleanWord (string str){
    int length = static_cast<int>(str.length());
    char *aux = new char [length+1];
    strcpy(aux, str.c_str());

    for (int i=length; i>1; i--){
        if (aux[strlen(aux)]==' ' && strlen(aux)>1){
            aux[strlen(aux)]='\0';

        }
    }
    if (aux[0]!=' '){
        aux[0] = static_cast<char>(toupper(aux[0]));
        for (int i=static_cast<int>(strlen(aux)); i>0; i--){
            aux[i]=static_cast<char>(tolower(aux[i]));
        }
    }
    str=aux;
    delete [] aux;
}



bool checkStuId(string id)
{
    char *identifier= nullptr;
        int tamano = static_cast<int> (id.length());
        identifier =new char [tamano+1];

        strcpy(identifier, id.c_str());

        for(int i=0;i<tamano;i++){
            if(identifier[i]<'0' || identifier[i]>'9'){
                return false;
            }
        }
        return true;

        //check if id belongs to a student (has only numbers)
        //returns true if student
        //returns false if professor or admin

}

bool checkResId(string identification)
{
    if (identification.length()!=7){
        return false;
    }else{
        for (int i=0;i<3;i++){
            if(!(((identification.c_str()[i]>='a')&&(identification.c_str()[i]<='z'))|| ((identification.c_str()[i]>='A')&& (identification.c_str()[i]<='Z')))){
                return false;
            }
        }

        for(int i=3;i<7;i++){
            if(!(identification.c_str()[i]>=0 && identification.c_str()[i]<=9)){

                return false;

        }

     }

   }
    return true;
}
