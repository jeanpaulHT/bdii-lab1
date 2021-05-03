//
// Created by esteb on 02-May-21.
//

#ifndef FILEORGANIZATION_TEST_P3_HPP
#define FILEORGANIZATION_TEST_P3_HPP

#include <iomanip>
#include "../headers//p3.h"

static double rand_payment ()
{
    double f = (double) rand() / RAND_MAX;
    return 0.0 + f * (10000.0 - 0.0);
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
    for (const auto& i : loaded)
    {
        P3::print(i);
    }
    auto student = vr.readRecord(NUM_ENTRIES);
    std::cout << std::endl;
    P3::print(student);

    std::cout << "Test 3 passed!";

}

#endif //FILEORGANIZATION_TEST_P3_HPP
