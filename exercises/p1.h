//
// Created by Jean Paul on 28/04/2021.
//

#ifndef FILEORG_P1_H
#define FILEORG_P1_H

#include "util.h"
using namespace std;

namespace P1
{

    struct Alumno
    {
        char codigo[5] = {'\0'};
        char nombre[11] = {'\0'};
        char apellidos[20] = {'\0'};
        char carrera[15] = {'\0'};

        bool operator==(const Alumno &rhs) const;
    };

    constexpr int ALUMNO_MB_SIZE[] = { 5, 11, 20, 15};


    class FixedRecord
    {

    private:
        string file;
    public:
        FixedRecord (string str);

        vector<Alumno> load ();

        void add (Alumno a);

        Alumno readRecord (int id);

    };


}


void print (P1::Alumno a);


#endif //FILEORG_P1_H
