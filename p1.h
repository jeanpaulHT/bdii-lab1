//
// Created by Jean Paul on 28/04/2021.
//

#ifndef FILEORG_P1_H
#define FILEORG_P1_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

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





void print(Alumno a);

#endif //FILEORG_P1_H
