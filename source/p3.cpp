#include <iostream>
#include <time.h>
#include "../test_headers//test_P3.hpp"
#include "../headers/p3.h"


int main() {
    srand(time(nullptr));
    test3();


    return 0;
}

bool P3::Alumno::operator==(const P3::Alumno &rhs) const {
    return this->nombre == rhs.nombre && this->apellidos == rhs.apellidos
    && this->mensualidad == rhs.mensualidad && this->carrera == rhs.carrera;
}
