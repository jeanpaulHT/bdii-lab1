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
    double f = (double) rand() / RAND_MAX;
    return 0.0 + f * (10000.0 - 0.0);
}

P2::Alumno random_student (int code)
{
    stringstream ss;

    P2::Alumno student;
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
    student.ciclo = rand();
    student.mensualidad = rand_m();

    return student;
}

void test2 ()
{
    constexpr auto CODE_SZ = sizeof(P2::Alumno::codigo);
    constexpr int NUM_ENTRIES = 3;

    string filename = "new_data_1";
    auto fr = P2::FixedRecord("../data/" + filename + ".dat");

    for (int code_int = 1; code_int <= NUM_ENTRIES; ++code_int)
    {
        auto student = random_student(code_int);
        fr.add(student);
    }

    auto loaded = fr.load();
    string last;
    stringstream ss;

    for (int i = 1; i <= NUM_ENTRIES; ++i)
    {
        ss << std::setfill('0') << std::setw(4) << i;
        last = ss.str();
        assert(memcmp(loaded[i].codigo, last.c_str(), CODE_SZ));
    }

    assert(memcmp(fr.readRecord(NUM_ENTRIES).codigo, last.c_str(), CODE_SZ));
    loaded.clear();

    bool erase_1 = fr.erase(NUM_ENTRIES);
    bool erase_2 = fr.erase(NUM_ENTRIES / 2);

    assert(erase_1);
    assert(erase_2);

    fr.add(random_student(NUM_ENTRIES + 1));
    fr.add(random_student(NUM_ENTRIES + 2));

    ss << std::setfill('0') << std::setw(4) << NUM_ENTRIES + 2;
    auto str = ss.str();
    assert(memcmp(fr.readRecord(NUM_ENTRIES).codigo, str.c_str(), CODE_SZ));

    assert(fr.read_head() == -1);

    fr.erase(1);
    std::cout << fr.read_head() << ' ';
    fr.erase(2);
    std::cout << fr.read_head() << ' ';

    for (auto i : fr.load()) {
        print(i);
        std::cout << std::endl;
    }


    std::cout << "Test 2 passed!";

}