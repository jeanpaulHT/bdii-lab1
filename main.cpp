#include <iostream>

#include "p1.h"



int main() {
    string fileName = "datos1";
    auto fr = FixedRecord("../" + fileName + ".txt");
    Alumno a {"1234", "AAA" ,"Par Edes", "CS",2};
    vector<Alumno> v;
    v.push_back(a);
    v.push_back(a);
    Alumno b =  {"2334", "BBB" ,"equis de", "Ing de cocina",1};
    v.push_back(b);

    fr.add(v);

    cout<<"------Prueba de add y readRecord------\n";
    Alumno res = fr.readRecord(0);
    print(res);
    cout<<"------Prueba de load------\n";
    auto loadVec = fr.load();
    int numAlumnos = 0;
    for(auto alumno: loadVec){
        cout<<"-------------------\n";
        cout<<"indice:"<<numAlumnos++<<'\n';
        print(alumno);
    }



    return 0;
}
