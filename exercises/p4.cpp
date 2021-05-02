//
// Created by Jean Paul on 02/05/2021.
//

#include "p4.h"

P4::VariableRecord::VariableRecord(std::string name): filename(name), metaData("../data/meta_new_data_2.dat") {
    std::fstream stream(filename, std::ios::out );
    if (!stream) exit(-2);
}




std::vector<P4::Matricula> P4::VariableRecord::load() {

    std::fstream stream(filename, std::ios::binary | std::ios::out | std::ios::in);

    std::vector<P4::Matricula> res{};
    std::string line;

    using str_sz_t = size_t;
    str_sz_t  sizeBuffer;


    Matricula matricula;
    while(stream.read( (char*)&sizeBuffer, sizeof(str_sz_t))){

        matricula.codigo.resize(sizeBuffer);
        stream.read( matricula.codigo.data(), sizeBuffer);

        stream.read( (char *) &matricula.ciclo , sizeof(matricula.ciclo));
        stream.read( (char *) &matricula.mensualidad , sizeof(matricula.mensualidad));

        stream.read( (char*)&sizeBuffer, sizeof(str_sz_t));
        matricula.observaciones.resize(sizeBuffer);
        stream.read( matricula.observaciones.data(), sizeBuffer);

        res.push_back(matricula);
    }
    stream.close();

    return res;
}

void P4::VariableRecord::add(const P4::Matricula &record) {
    auto[codigo, ciclo, mensualidad, observaciones] = record;

    std::fstream stream(filename, std::ios::binary | std::ios::in | std::ios::out| std::ios::app);
    stream.seekp(0, std::ios::end);

    // codigo
    using str_sz_t = decltype(record.codigo.size());
    char buffer[sizeof(str_sz_t)];
    *(str_sz_t*)(buffer) = codigo.size();
    stream.write(buffer, sizeof(str_sz_t));
    stream.write(codigo.data() , codigo.size());

    //ciclo
    stream.write( (char*) &ciclo, sizeof(ciclo));
    //mensualidad
    stream.write( (char*) &mensualidad, sizeof(mensualidad));
    //observaciones
    *(str_sz_t*)(buffer) = observaciones.size();
    stream.write(buffer, sizeof(str_sz_t));
    stream.write(observaciones.data() , observaciones.size());

    metaData.add(sizeof(str_sz_t) * 2 + observaciones.size() + codigo.size()
    + sizeof(ciclo) + sizeof(mensualidad) );
    stream.close();

}

P4::Matricula P4::VariableRecord::readRecord(int pos) {

    std::fstream stream(filename, std::ios::in | std::ios::binary);
    stream.seekp(metaData.readRecord(pos));

    using str_sz_t = size_t;
    str_sz_t  sizeBuffer;


    Matricula matricula;
    stream.read( (char*)&sizeBuffer, sizeof(str_sz_t));

    matricula.codigo.resize(sizeBuffer);
    stream.read( matricula.codigo.data(), sizeBuffer);

    stream.read( (char *) &matricula.ciclo , sizeof(matricula.ciclo));
    stream.read( (char *) &matricula.mensualidad , sizeof(matricula.mensualidad));

    stream.read( (char*)&sizeBuffer, sizeof(str_sz_t));
    matricula.observaciones.resize(sizeBuffer);
    stream.read( matricula.observaciones.data(), sizeBuffer);

    return matricula;
}

P4::metaData::metaData(std::string name):filename(name) {
    std::fstream stream(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!stream) exit(-2);
    stream.close();
}

void P4::metaData::add(size_t size) {

    std::fstream stream(filename, std::ios::in | std::ios::out| std::ios::binary);

    size_t pos = 0;

    stream.seekp( 0, std::ios::end);
    if(stream.tellg() != 0){
        size_t temp;

        stream.seekp( -8, std::ios::cur);
        stream.read( (char*) &pos, sizeof(pos));
        stream.read( (char*) &temp, sizeof(temp));
        pos = pos + temp;
    }

    stream.write((char *) &pos, sizeof(pos));
    stream.write((char *) &size, sizeof(size));

    stream.close();
}

int P4::metaData::readRecord(int pos) {

    pos--;
    int resPos = 0;
    std::fstream stream(filename, std::ios::in | std::ios::binary);


    size_t offset = 8;
    stream.seekp(pos * offset);

    stream.read( (char*) &resPos, sizeof(resPos));
    stream.close();


    return resPos;
}

std::vector<std::pair<size_t, size_t>> P4::metaData::readAll() {

    std::fstream stream(filename, std::ios::binary | std::ios::out | std::ios::in);

    std::vector<std::pair<size_t,size_t>> res{};
    std::string line;

    using str_sz_t = size_t;
    str_sz_t  sizeBuffer;
    str_sz_t  sizeBuffer2;



    Matricula matricula;
    while(stream.read( (char*)&sizeBuffer, sizeof(str_sz_t))){
        stream.read( (char*)&sizeBuffer2, sizeof(str_sz_t));

        res.push_back({sizeBuffer,sizeBuffer2});

    }
    stream.close();

    return res;


}

bool P4::Matricula::operator==(const P4::Matricula &rhs) const {
    return this->mensualidad == rhs.mensualidad && this->codigo == rhs.codigo &&
            this->observaciones == rhs.observaciones && this->ciclo == rhs.ciclo;
}
