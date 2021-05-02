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



    struct Metadata
    {
        int position;
        int size;
    };

    struct VariableRecord
    {
        std::string headerFile;
        std::string filename;

        explicit VariableRecord (std::string name);

        std::vector<Matricula> load();

        void add(Matricula record);

        Matricula readRecord(int pos);

    };

    static void print (const Matricula& m)
    {
        std::cout << m.codigo << ' ' << m.ciclo << ' ' << m.mensualidad << ' '
                  << m.observaciones << '\n';
    }
};

#endif //FILEORGANIZATION_P4_H
