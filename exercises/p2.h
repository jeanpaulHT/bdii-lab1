//
// Created by Jean Paul on 29/04/2021.
//

#ifndef FILEORG_P2_H
#define FILEORG_P2_H

#include "util.h"

using namespace std;

namespace P2
{

    struct Alumno
    {
        char codigo[5] = {'\0'};
        char nombre[11] = {'\0'};
        char apellidos[20] = {'\0'};
        char carrera[15] = {'\0'};

        int ciclo = 0;
        float mensualidad = 0.0f;

        int nextDel = 0;
    };


    class FixedRecord
    {

    private:
        string file;
        int head = -1;

    public:
        explicit FixedRecord (string str);

        vector<Alumno> load ();

        void add (Alumno a);

        Alumno readRecord (int id);

        bool erase (int pos);

        [[nodiscard]] int read_head() const {
            return head;
        }
    };

};

void print (P2::Alumno a);


#endif //FILEORG_P2_H
