#ifndef FILEORGANIZATION_TEST_P1_HPP
#define FILEORGANIZATION_TEST_P1_HPP

#include <iomanip>
#include <cassert>
#include "../headers/p1.h"

static double rand_payment ()
{
    double f = (double) rand() / RAND_MAX;
    return 0.0 + f * (10000.0 - 0.0);
}

P1::Alumno random_p1_student (int code)
{
    stringstream ss;

    P1::Alumno student;
    ss << std::setfill('0') << std::setw(4) << code;
    memcpy(student.codigo, ss.str().c_str(), sizeof(student.codigo));

    for (int i = 0; i < sizeof(student.nombre) - 1; ++i)
    {
        student.nombre[i] = 'a' + rand() % 26;
    }
    for (int i = 0; i < sizeof(student.apellidos) - 1; ++i)
    {
        student.apellidos[i] = 'a' + rand() % 26;
    }
    for (int i = 0; i < sizeof(student.carrera) - 1; ++i)
    {
        student.carrera[i] = 'a' + rand() % 26;
    }

    return student;
}

void test1 ()
{
    constexpr auto CODE_SZ = sizeof(P1::Alumno::codigo);
    constexpr int NUM_ENTRIES = 100;

    string fileName = "datos1";
    auto fr = P1::FixedRecord("../data/" + fileName + ".txt");

    for (int code_int = 1; code_int <= NUM_ENTRIES; ++code_int)
    {
        auto student = random_p1_student(code_int);
        fr.add(student);
    }

//    cout << "------Prueba de load------\n";
    auto loadVec = fr.load();
    assert(loadVec.size() == NUM_ENTRIES);
    cout << "Passed check for add"  << '\n';

    int numAlumnos = 0;
    std::stringstream ss;

    for (int i = 0; i < loadVec.size(); ++i) {
        ss.str("");
        ss << std::setfill('0') << std::setw(CODE_SZ - 1) << i + 1;
        auto last = ss.str();
        assert(memcmp(loadVec[i].codigo, last.c_str(), CODE_SZ) == 0);
        cout << "Passed check for load on student #" << i + 1 << '\n';
    }

    std::cout << "Passed all tests for load\n";

    numAlumnos = 0;
    for (const auto& alumno: loadVec)
    {
//        cout << "-------------------\n";
//        print(alumno);
//        print(fr.readRecord(numAlumnos));
        assert(alumno == fr.readRecord(numAlumnos));
        cout << "Passed check for readRecord on student #" << ++numAlumnos << '\n';
    }

    std::cout << "Test 1 passed!";
}

#endif //FILEORGANIZATION_TEST_P1_HPP
