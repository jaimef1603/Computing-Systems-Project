#include <iostream>
#include "VirtualCampus.h"

using namespace std;

int main()
{
    //ofstream file("FileDePrueba", ios::trunc | ios::binary);
     VirtualCampus v1;

     v1.start();

     v1.run();

     v1.stop();

/*
     Seminar *prueba = new Seminar("NOMBRE", "IDSIETE", nullptr, 8);
     Student *estu1  = new Student("jaime", nullptr);
     Student *estu2  = new Student("jorge", nullptr);
     estu1->enroll(prueba);
     estu2->enroll(prueba);
     prueba->setdate(Date(1, 2, 2018));
     if (file){

         file<<*prueba;
         delete prueba;
         prueba = new Seminar();
         file.close();
         ifstream file2("FileDePrueba", ios::in | ios::binary);
         if (file2){

             file2>>*prueba;
             cout<<prueba->getname()
                <<prueba->getIdentification()
               <<prueba->getdate()
              <<prueba->getmaxseats()<<endl;
         }else {
             cerr<<"Input File not loaded\n";
         }



     }else{
         cerr<<"Output File not loaded\n";
     }

*/


    return 0;
}
