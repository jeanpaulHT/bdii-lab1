//
// Created by Jean Paul on 29/04/2021.
//

#include <iomanip>
#include "exercises/p1.h"
#include "exercises/p2.h"


void testp1 ()
{
    bool add = true;
    string fileName = "datos1";
    auto fr = P1::FixedRecord("../data/" + fileName + ".txt");
    P1::Alumno b = { "0201", "asdasd", "Paredes XD", "Ing. Cocina" };


    cout << "------readRecord------\n";
    P1::Alumno res = fr.readRecord(3);
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
    for (auto alumno: loadVec)
    {
        assert(alumno == fr.readRecord(numAlumnos++));
    }

    cout << "is ok c: \n";


}

static double rand_m ()
{
    double f = (double)rand() / RAND_MAX;
    return 0.0 + f * (10000.0 - 0.0);
}

void test2 ()
{
    string filename = "new_data_1";
    auto fr = P2::FixedRecord("../data/" + filename + ".dat");

    stringstream ss;
    for (int code_int = 0; code_int < 10; ++code_int)
    {
        P2::Alumno student;
        ss << std::setfill('0') << std::setw(4) << code_int;
        memcpy(student.codigo, ss.str().c_str(), sizeof(student.codigo));
        ss.str("");

        for (int i = 0; i < sizeof(student.nombre) - 1; ++i)
        {
            student.nombre[i] = 'a' + rand()%26;
        }
        for (int i = 0; i < sizeof(student.apellidos) - 1; ++i)
        {
            student.apellidos[i] = 'a' + rand()%26;
        }
        for (int i = 0; i < sizeof(student.carrera) - 1; ++i)
        {
            student.carrera[i] = 'a' + rand()%26;
        }
        student.ciclo = rand();
        student.mensualidad = rand_m();

        fr.add(student);
    }
    for (auto student : fr.load()) {
        print(student);
        std::cout << std::endl;
    }



}