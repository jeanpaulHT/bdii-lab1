//
// Created by Jean Paul on 28/04/2021.
//

#include "p1.h"

void print(P1::Alumno a){
    cout<<"codigo: "<<a.codigo<<"\nnombre:" <<a.nombre<<"\napellidos:"<<a.apellidos<<"\ncarrera:"<<a.carrera
    <<"\n";

}


P1::FixedRecord::FixedRecord(string str):file(str) {
}

vector<P1::Alumno> P1::FixedRecord::load() {
    ifstream inFile(file,ios::in);

    if(!inFile.is_open()) throw "File does not exist";

    vector<Alumno> res {};
    Alumno  temp;
    string str;
    while(inFile.read((char *) &temp, sizeof(Alumno))){
        res.push_back(temp);
        inFile.ignore();
    }
    inFile.close();
    return res;
}

void P1::FixedRecord::add(P1::Alumno record) {
    ofstream outFile(file, ios::app);
    if(!outFile.is_open()) throw "File does not exist";
    outFile.write((char*) &record, sizeof(Alumno) );


    outFile<<"\n";
    outFile.close();
}


P1::Alumno P1::FixedRecord::readRecord(int pos) {
    ifstream inFile(file);

    Alumno alumno {};
    inFile.seekg(pos * (sizeof(Alumno) ) , ios::beg);
    // it works
    //
    inFile.read((char *) &alumno, sizeof(Alumno));
    inFile.close();

    return alumno;
}
