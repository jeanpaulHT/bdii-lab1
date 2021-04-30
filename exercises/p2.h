//
// Created by Jean Paul on 29/04/2021.
//

#ifndef FILEORG_P2_H
#define FILEORG_P2_H

#include "util.h"

using namespace std;

struct p2{

    struct Alumno{

        char codigo [5];
        char nombre [11];
        char apellidos [20];
        char carrera [15];

        int NextDel = 0;
    };


    class FixedRecord{

    private:
        string file;
        int head = 0;
    public:
        FixedRecord(string str);
        vector<Alumno> load();
        void add(Alumno a);
        void add(vector<Alumno> vec);
        Alumno readRecord(int pos);
        bool erase(int pos);

    };

};


#endif //FILEORG_P2_H
