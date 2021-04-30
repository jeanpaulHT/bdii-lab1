//
// Created by Jean Paul on 29/04/2021.
//

#include "p2.h"

P2::FixedRecord::FixedRecord(string str) : file(std::move(str)) {
    fstream stream(str, ios::out | ios::binary);
}

vector<P2::Alumno> P2::FixedRecord::load() {
    return vector<Alumno>();
}

P2::Alumno P2::FixedRecord::readRecord(int i) {
    return P2::Alumno();
}


void print(P2::Alumno a) {
    cout << "codigo: " << a.codigo << "\nnombre:" << a.nombre << "\napellidos:"
         << a.apellidos << "\ncarrera:" << a.carrera<<"\nmensualidad:"<<a.mensualidad
         <<"\nciclo:"<<a.ciclo<<"\nnextDel:"<<a.nextDel<< "\n";

}

void P2::FixedRecord::add (P2::Alumno a)
{
    fstream stream(file, ios::out | ios::binary);
    if (!stream) exit(-1);

    if (head == -1) // no deleted entries, add at end and be happy
    {
        stream.seekp(0, ios_base::end);
        stream.write((char*) &a, sizeof(Alumno));
        stream << '\n';
    }
}
