//
// Created by Jean Paul on 28/04/2021.
//

#ifndef FILEORG_P1_H
#define FILEORG_P1_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */
#define CR_SIZE 1
#elif defined(_WIN32) || defined(_WIN64) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
#define CR_SIZE 2
#else
#define CR_SIZE 1                       /* Im just betting here, but you're probably using MAC */
#endif

using namespace std;

namespace P1
{

    struct Alumno
    {
        char codigo[5] = { '\0' };
        char nombre[11] = { '\0' };
        char apellidos[20] = { '\0' };
        char carrera[15] = { '\0' };

        bool operator == (const Alumno& rhs) const;
    };

    constexpr int ALUMNO_MB_SIZE[] = { 5, 11, 20, 15 };


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

void print (P1::Alumno a)
{
    cout << "codigo: " << a.codigo << "\nnombre:" << a.nombre << "\napellidos:"
         << a.apellidos << "\ncarrera:" << a.carrera
         << "\n";

}


P1::FixedRecord::FixedRecord (string str) : file(std::move(str))
{
    fstream stream(file, std::ios::out);
    if (!stream)
    {
        std::cerr << "ERROR: couldn't open file: " << file << '\n';
        exit(-2);
    }
}

static inline void rtrim (std::string& s)
{
    s.erase(
        std::find_if(
            s.rbegin(), s.rend(), [] (unsigned char ch)
            {
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
        line.resize(sizeof(Alumno), ' ');
        int pos = 0;
        for (int length : ALUMNO_MB_SIZE)
        {
            for (int i = length - 1; line[pos + i] == ' ' && i >= 0; --i)
                line[pos + i] = '\0';
            pos += length;
        }
        res.emplace_back(*(Alumno*) line.data());
    }
    inFile.close();
    return res;
}

void P1::FixedRecord::add (P1::Alumno record)
{
    using Arr = char[sizeof(Alumno)];

    ofstream outFile(file, ios::app);
    if (!outFile.is_open()) exit(-1);

    // this is just bad code. It's also dumb code. Furthermore, it's bad and
    // dumb code that I shouldn't have needed to implement, but was forced to
    // because of the data layout in the input file. WHY?
    auto& buffer = *(Arr*) &record;
    std::replace(begin(buffer), end(buffer), '\0', ' ');
    outFile.write(buffer, sizeof(Alumno));

    outFile << "\n";
    outFile.close();
}



P1::Alumno P1::FixedRecord::readRecord (int id)
{
    ifstream inFile(file, ios::binary);

    Alumno alumno{};
    string line;

    inFile.seekg(id * (sizeof(Alumno) + sizeof(char) * CR_SIZE), ios::beg);
    getline(inFile, line);

    int pos = 0;
    for (int length : ALUMNO_MB_SIZE)
    {
        for (int i = length - 1; line[pos + i] == ' ' && i >= 0; --i)
            line[pos + i] = '\0';
        pos += length;
    }
    alumno = *(Alumno*) line.data();
    inFile.close();

    return alumno;
}

bool P1::Alumno::operator == (const P1::Alumno& rhs) const
{
    return strcmp(this->codigo, rhs.codigo) == 0 &&
           strcmp(this->nombre, rhs.nombre) == 0 &&
           strcmp(this->apellidos, rhs.apellidos) == 0 &&
           strcmp(this->carrera, rhs.carrera) == 0;
}

#endif //FILEORG_P1_H
