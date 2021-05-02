//
// Created by Jean Paul on 02/05/2021.
//

#ifndef FILEORGANIZATION_P4_H
#define FILEORGANIZATION_P4_H

#include "util.h"
#include <cmath>

namespace P4{

    struct Matricula{
        std::string codigo;
        int ciclo;
        float mensualidad;
        std::string observaciones;

        bool operator==(const Matricula &rhs) const;
    };



    struct metaData
    {

        std::string filename;

        explicit metaData (std::string name);

        void add (size_t size);

        int readRecord ( int pos);

        std::vector<std::pair<size_t, size_t>> readAll();
    };

    struct VariableRecord
    {

        std::string filename;
        metaData metaData;

        explicit VariableRecord (std::string name);

        std::vector<Matricula> load ();

        void add (const Matricula& record);

        Matricula readRecord (int pos);
    };

    static void print (const Matricula& m)
    {
        std::cout << m.codigo << ' ' << m.ciclo << ' ' << m.mensualidad << ' '
                  << m.observaciones << '\n';
    }
};

#endif //FILEORGANIZATION_P4_H
