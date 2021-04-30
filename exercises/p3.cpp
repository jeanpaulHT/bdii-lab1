//
// Created by esteb on 30-Apr-21.
//

#include "p3.h"
#include <iomanip>
#include <fstream>

std::vector<P3::Alumno> P3::VariableRecord::load ()
{
    std::fstream stream(filename, std::ios::in);
    std::vector<Alumno> ret;
    std::string line;

    Alumno student;
    for (; std::getline(stream, line, '\n');)
    {
        std::istringstream iss(line);
        std::getline(iss, student.nombre, '|');
        std::getline(iss, student.apellidos, '|');
        std::getline(iss, student.carrera, '|');
        iss >> student.mensualidad;
    }
    return ret;
}

void P3::VariableRecord::add (const P3::Alumno& record)
{
    auto&[name, lname, career, mens] = record;
    std::stringstream ss;
    ss << std::ios::fixed
       << name << '|' << lname << '|' << career << '|' << mens << '\n';

    std::fstream stream(filename, std::ios::in | std::ios::out);
    stream.seekp(0, std::ios_base::end);
    auto str = ss.str();
    stream.write(str.data(), str.size());
    if (!stream) exit(-1);
}

P3::VariableRecord::VariableRecord (std::string name)
    : filename(std::move(name))
{
    std::fstream stream(filename, std::ios::in);
    if (!stream) {
        stream.open(filename, std::ios::out);
        if (!stream) exit(-2);
    }
}