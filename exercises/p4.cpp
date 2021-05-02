//
// Created by Jean Paul on 02/05/2021.
//

#include "p4.h"

#include <utility>

using namespace std;

P4::VariableRecord::VariableRecord (std::string name)
    : filename(std::move(name)),
      headerFile("../data/meta_new_data_2.dat")
{
    fstream stream(filename, std::ios::out);
    if (!stream) exit(-2);
    fstream header(headerFile, std::ios::out);
    if (!header) exit(-2);
}

void P4::VariableRecord::add (P4::Matricula record)
{
    auto&[codigo, ciclo, mensualidad, observaciones] = record;
    fstream stream(filename, ios::out | ios::in | ios::ate | ios::binary);
    fstream header(headerFile, ios::out | ios::in | ios::ate | ios::binary);

    int recordSize = 2 * sizeof(int) + observaciones.size() + codigo.size()
                     + sizeof(ciclo) + sizeof(mensualidad);
    Metadata metadata{ .position = (int) stream.tellg(), .size = recordSize };
    header.write((char*) &metadata, sizeof(Metadata));

    char buffer[sizeof(int)];
    *(int*) (buffer) = codigo.size();
    stream.write(buffer, sizeof(int));
    stream.write(codigo.data(), codigo.size());

    stream.write((char*) &ciclo, sizeof(ciclo));

    stream.write((char*) &mensualidad, sizeof(mensualidad));

    *(int*) (buffer) = observaciones.size();
    stream.write(buffer, sizeof(int));
    stream.write(observaciones.data(), observaciones.size());
}

vector<P4::Matricula> P4::VariableRecord::load ()
{
    std::fstream stream(
        filename, std::ios::binary | std::ios::out | std::ios::in);

    std::vector<P4::Matricula> res{};
    std::string line;

    int sizeBuffer;


    Matricula matricula;
    while (stream.read((char*) &sizeBuffer, sizeof(int)))
    {

        matricula.codigo.resize(sizeBuffer);
        stream.read(matricula.codigo.data(), sizeBuffer);

        stream.read((char*) &matricula.ciclo, sizeof(matricula.ciclo));
        stream.read((char*) &matricula.mensualidad,
                    sizeof(matricula.mensualidad));

        stream.read((char*) &sizeBuffer, sizeof(int));
        matricula.observaciones.resize(sizeBuffer);
        stream.read(matricula.observaciones.data(), sizeBuffer);

        res.push_back(matricula);
    }
    return res;
}

P4::Matricula P4::VariableRecord::readRecord (int pos)
{
    fstream stream(filename, ios::in | ios::binary);
    fstream header(headerFile, ios::in | ios::binary);

    Metadata metadata;
    header.seekg(sizeof(Metadata) * (pos - 1));
    header.read((char*) &metadata, sizeof(Metadata));

    auto&[recordPosition, recordSize] = metadata;

    stream.seekg(recordPosition);
    Matricula matricula;

    int sizeBuffer;
    stream.read((char*) &sizeBuffer, sizeof(int));

    matricula.codigo.resize(sizeBuffer);
    stream.read(matricula.codigo.data(), sizeBuffer);

    stream.read((char*) &matricula.ciclo, sizeof(matricula.ciclo));
    stream.read((char*) &matricula.mensualidad, sizeof(matricula.mensualidad));

    stream.read((char*) &sizeBuffer, sizeof(int));
    matricula.observaciones.resize(sizeBuffer);
    stream.read(matricula.observaciones.data(), sizeBuffer);

    return matricula;
}


bool P4::Matricula::operator == (const P4::Matricula& rhs) const
{
    return this->mensualidad == rhs.mensualidad && this->codigo == rhs.codigo &&
           this->observaciones == rhs.observaciones && this->ciclo == rhs.ciclo;
}
