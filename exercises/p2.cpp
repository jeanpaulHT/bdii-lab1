//
// Created by Jean Paul on 29/04/2021.
//

#include "p2.h"


P2::FixedRecord::FixedRecord (string str) : file(std::move(str))
{
    fstream stream(file, ios::out);
    if (!stream) exit(-2);

}

vector<P2::Alumno> P2::FixedRecord::load ()
{
    vector<P2::Alumno> ret;
    fstream stream(file, ios::in | ios::binary);
    char buffer[sizeof(Alumno)];
    while (stream.read(buffer, sizeof(Alumno)))
    {
        Alumno& toAdd = *(Alumno*) buffer;
        ret.push_back(toAdd);
    }
    return ret;
}

P2::Alumno P2::FixedRecord::readRecord (int i)
{
    return P2::Alumno();
}


void print (P2::Alumno a)
{
    cout << "codigo: " << a.codigo << "\nnombre:" << a.nombre << "\napellidos:"
         << a.apellidos << "\ncarrera:" << a.carrera << "\nmensualidad:"
         << a.mensualidad
         << "\nciclo:" << a.ciclo << "\nnextDel:" << a.nextDel << "\n";

}

void P2::FixedRecord::add (P2::Alumno a)
{
    fstream stream(file, ios::in | ios::out | ios::binary);
    if (!stream) exit(-1);

    if (head == -1) // no deleted entries, add at end and be happy
    {
        stream.seekg(0, ios_base::end);
        stream.write((char*) &a, sizeof(Alumno));
//        print(a);
    }
}