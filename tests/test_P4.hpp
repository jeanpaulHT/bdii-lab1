//
// Created by esteb on 02-May-21.
//

#ifndef FILEORGANIZATION_TEST_P4_HPP
#define FILEORGANIZATION_TEST_P4_HPP

#include <iomanip>
#include <cassert>
#include "../src/p4.h"

static double rand_payment ()
{
    double f = (double) rand() / RAND_MAX;
    return 0.0 + f * (10000.0 - 0.0);
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

#endif //FILEORGANIZATION_TEST_P4_HPP
