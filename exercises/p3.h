//
// Created by esteb on 30-Apr-21.
//

#ifndef FILEORGANIZATION_P3_H
#define FILEORGANIZATION_P3_H

#include <string>
#include <vector>
#include <iostream>

namespace P3
{
    struct Alumno
    {
        std::string nombre;
        std::string apellidos;
        std::string carrera;
        float mensualidad;
    };

    struct VariableRecord
    {

        std::string filename;

        explicit VariableRecord (std::string name);

        std::vector<Alumno> load ();

        void add (const Alumno& record);

        Alumno readRecord (int pos);
    };

    static void print (const Alumno& a)
    {
        std::cout << a.nombre << ' ' << a.apellidos << ' ' << a.carrera << ' '
                  << a.mensualidad << '\n';
    }
};


#endif //FILEORGANIZATION_P3_H
