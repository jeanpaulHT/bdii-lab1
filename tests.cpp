//
// Created by Jean Paul on 29/04/2021.
//

#include "exercises/p1.h"

void testp1 ()
{
    bool add = true;
    string fileName = "datos1";
    auto fr = P1::FixedRecord("../data/" + fileName + ".txt");
    P1::Alumno b = { "0201", "asdasd", "Paredes XD", "Ing. Cocina" };



    cout<<"------readRecord------\n";
    P1::Alumno res = fr.readRecord( 3);
    print(res);
    cout << "------Prueba de load------\n";
    auto loadVec = fr.load();
    int numAlumnos = 0;
    for (auto alumno: loadVec)
    {
        cout << "-------------------\n";
        assert(alumno == fr.readRecord(numAlumnos));
        cout << "indice:" << numAlumnos++ << '\n';
        print(alumno);
    }
    cout << "------Prueba de add------\n";
    fr.add(b);
    loadVec = fr.load();
    assert(numAlumnos + 1 == loadVec.size());
    numAlumnos = 0;
    for (auto alumno: loadVec){
        assert(alumno == fr.readRecord(numAlumnos++));
    }

    cout<<"is ok c: \n";


}


void test2 ()
{

}