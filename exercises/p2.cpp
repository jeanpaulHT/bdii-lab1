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

P2::Alumno P2::FixedRecord::readRecord (int id)
{
    id--;
    fstream stream(file, ios::in | ios::binary);
    char buffer[sizeof(Alumno)];
    stream.seekp(id * sizeof(Alumno));
    stream.read(buffer, sizeof(Alumno));

    if (stream.fail())
    {
        std::cerr << "not found\n";
        exit(-1);
    }
    return *(Alumno*) buffer;
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
    using Node = decltype(Alumno::nextDel);
    static constexpr int offset = offsetof(Alumno, nextDel);

    fstream stream(file, ios::in | ios::out | ios::binary);
    if (!stream) exit(-1);

    if (head == -1) // no deleted entries, add at end and be happy
    {
        stream.seekg(0, ios_base::end);
        stream.write((char*) &a, sizeof(Alumno));
    }
    else // fuck
    {
        int prev = head - 1;
        stream.seekg(prev * sizeof(Alumno) + offset);
        stream.read((char*) &head, sizeof(Node)); // head is next

        stream.seekp(prev * sizeof(Alumno));
        stream.write((char*) &a, sizeof(Alumno)); // overwrite
    }
}

bool P2::FixedRecord::erase (int index)
{
    auto pos = index - 1;
    // do push front on a int linked list
    using Node = decltype(Alumno::nextDel);
    static constexpr int offset = offsetof(Alumno, nextDel);

    fstream stream(file, ios::in | ios::out | ios::binary);

    Node node;
    stream.seekg(pos * sizeof(Alumno) + offset);
    stream.read((char*) &node, sizeof(Node));

    if (node != 0 || !stream) return false; // already deleted or nonexistent

    stream.seekp(pos * sizeof(Alumno) + offset);
    stream.write((char*) &head, sizeof(Node));

    this->head = index;
    return true;
}


