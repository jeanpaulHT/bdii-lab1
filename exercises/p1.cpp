//
// Created by Jean Paul on 28/04/2021.
//

#include "p1.h"
#include <cstring>

void print (P1::Alumno a)
{
    cout << "codigo: " << a.codigo << "\nnombre:" << a.nombre << "\napellidos:"
         << a.apellidos << "\ncarrera:" << a.carrera
         << "\n";

}


P1::FixedRecord::FixedRecord (string str) : file(str)
{
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}


vector<P1::Alumno> P1::FixedRecord::load ()
{
    ifstream inFile(file, ios::in);

    if (!inFile.is_open()) exit(-1);
    vector<Alumno> res{};
    string line;

    while (getline(inFile, line))
    {
        char buffer[sizeof(Alumno)];
        int position = 0;
        for (int length : ALUMNO_MB_SIZE) {
            auto member = line.substr(position, length);
            rtrim(member);
            memcpy(buffer + position, member.c_str(), member.size() + 1);
            position += length;
        }
        res.emplace_back(*(Alumno*) buffer);
    }
    inFile.close();
    return res;
}

void P1::FixedRecord::add (P1::Alumno record)
{
    using Arr = char[sizeof (Alumno)];

    ofstream outFile(file, ios::app);
    if (!outFile.is_open()) exit(-1);
    auto& buffer = *(Arr*) &record;
    std::replace(begin(buffer), end(buffer), '\0', ' ');
    outFile.write(buffer, sizeof(Alumno));

    outFile << "\n";
    outFile.close();
}


P1::Alumno P1::FixedRecord::readRecord (int pos)
{
    ifstream inFile(file);

    Alumno alumno{};
    inFile.seekg(pos * (sizeof(Alumno)), ios::beg);
    // it works
    //
    inFile.read((char*) &alumno, sizeof(Alumno));
    inFile.close();

    return alumno;
}
