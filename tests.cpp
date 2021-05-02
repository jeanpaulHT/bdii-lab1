//
// Created by Jean Paul on 29/04/2021.
//

#include <iomanip>
#include "exercises/p1.h"
#include "exercises/p2.h"
#include "exercises/p3.h"
#include "exercises/p4.h"



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


P2::Alumno random_p2_student (int code)
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
    student.mensualidad = rand_payment();

    return student;
}

P3::Alumno random_p3_student ()
{
    static constexpr int TEST_MAX_NAME_SZ = 20;
    static constexpr int TEST_MAX_LNAME_SZ = 25;
    static constexpr int TEST_MAX_CAREER_SZ = 15;
    stringstream ss;

    constexpr auto rlen =
        [] (int limit) { return rand() % (limit / 2) + limit / 2; };

    P3::Alumno student;
    student.mensualidad = rand_payment();

    student.nombre.resize(rlen(TEST_MAX_NAME_SZ));
    student.apellidos.resize(rlen(TEST_MAX_LNAME_SZ));
    student.carrera.resize(rlen(TEST_MAX_CAREER_SZ));

    for (auto m_ptr : { &student.nombre, &student.apellidos, &student.carrera })
    {
        for (auto& c : *m_ptr)
            c = 'a' + rand() % 26;
    }
    return student;
}

P4::Matricula random_p4_matricula ()
{
    static constexpr int TEST_MAX_NAME_COD= 5;
    static constexpr int TEST_MAX_LNAME_OBS = 30;
    stringstream ss;

    constexpr auto rlen =
            [] (int limit) { return rand() % (limit / 2) + limit / 2; };

    P4::Matricula matricula;
    matricula.ciclo = rand() %20;
    matricula.mensualidad = rand_payment();


    matricula.codigo.resize(rlen(TEST_MAX_NAME_COD));
    matricula.observaciones.resize(rlen(TEST_MAX_LNAME_OBS));

    for(auto &c: matricula.codigo){
        c = '0' + rand() % 9;
    }

    for(auto &c: matricula.observaciones){
        c = 'a' + rand() % 26;
    }

    return matricula;
}


void testp1 ()
{
    constexpr int NUM_ENTRIES = 10;

    string fileName = "datos1";
    auto fr = P1::FixedRecord("../data/" + fileName + ".txt");

    for (int code_int = 1; code_int <= NUM_ENTRIES; ++code_int)
    {
        auto student = random_p1_student(code_int);
        fr.add(student);
    }

//    cout << "------Prueba de load------\n";
    auto loadVec = fr.load();
    int numAlumnos = 0;
    for (auto alumno: loadVec)
    {
        cout << "-------------------\n";
        print(alumno);
        print(fr.readRecord(numAlumnos));
        assert(alumno == fr.readRecord(numAlumnos));
        cout << "indice:" << numAlumnos << '\n';

        numAlumnos++;
    }

    std::cout << "Test 1 passed!";
}


void test2 ()
{
    constexpr auto CODE_SZ = sizeof(P2::Alumno::codigo);
    constexpr int NUM_ENTRIES = 10;

    string filename = "new_data_1";
    auto fr = P2::FixedRecord("../data/" + filename + ".dat");

    for (int code_int = 1; code_int <= NUM_ENTRIES; ++code_int)
    {
        auto student = random_p2_student(code_int);
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

    fr.add(random_p2_student(NUM_ENTRIES + 1));
    fr.add(random_p2_student(NUM_ENTRIES + 2));

    ss << std::setfill('0') << std::setw(4) << NUM_ENTRIES + 2;
    auto str = ss.str();
    assert(memcmp(fr.readRecord(NUM_ENTRIES).codigo, str.c_str(), CODE_SZ));

    assert(fr.read_head() == -1);

    fr.erase(1);
    fr.erase(2);
    assert(!fr.erase(2));

    for (auto i : fr.load())
    {
        print(i);
        std::cout << std::endl;
    }


    std::cout << "Test 2 passed!";

}

void test3 ()
{
    constexpr int NUM_ENTRIES = 100;

    string filename = "var_data_1";
    auto vr = P3::VariableRecord("../data/" + filename + ".dat");

    for (int code_int = 1; code_int <= NUM_ENTRIES; ++code_int)
    {
        auto student = random_p3_student();
        vr.add(student);
    }

    auto loaded = vr.load();
    for (const auto& i : loaded) {
        P3::print(i);
    }
    auto student = vr.readRecord(NUM_ENTRIES);
    std::cout << std::endl;
    P3::print(student);

    std::cout << "Test 3 passed!";

}




void test4 ()
{
    constexpr int NUM_ENTRIES = 10;

    string filename = "new_data_2";

    auto vr = P4::VariableRecord("../data/" + filename + ".dat");

    P4::Matricula m {"1023",3,2020.13,"XD le falta descansito"};
    P4::Matricula m1 {"10223",3,2022.13,"XD"};
    P4::Matricula m2 {"1024",0,10.13,"le falta"};

    for (int code_int = 1; code_int <= NUM_ENTRIES; ++code_int)
    {
        auto matricula = random_p4_matricula();
        vr.add(matricula);
    }

    vr.add(m);
    vr.add(m2);
    vr.add(m1);

    auto mload = vr.load();
    assert(mload.size() == NUM_ENTRIES + 3);

    int posMatricula = 1;
    for (const auto& i : vr.load()){
        print(i);
        assert(i == vr.readRecord(posMatricula));
        posMatricula++;
    }
    std::cout << "Test 4 passed!";
}