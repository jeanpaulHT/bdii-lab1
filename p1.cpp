//
// Created by Jean Paul on 28/04/2021.
//

#include "p1.h"

void print(Alumno a){
    cout<<"codigo: "<<a.codigo<<"\nnombre:" <<a.nombre<<"\napellidos:"<<a.apellidos<<"\ncarrera:"<<a.carrera
    <<"\nnextDel:"<<a.NextDel<<'\n';

}

FixedRecord::FixedRecord(string str):file(str) {

}

vector<Alumno> FixedRecord::load() {
    ifstream inFile(file,ios::in | ios::binary);


    if(!inFile.is_open()) throw "File does not exist";

    vector<Alumno> res {};
    Alumno  temp;
    string str;
    while(inFile.read((char *) &temp, sizeof(Alumno))){
        res.push_back(temp);
        getline(inFile,str);
    }

    return res;
}



void FixedRecord::add(Alumno record) {
    ofstream outFile(file, ios::app | ios::binary);
    if(!outFile.is_open()) throw "File does not exist";
    outFile.write((char*) &record, sizeof(Alumno));

    outFile<<"\n";
}


void FixedRecord::add(vector<Alumno> vec) {
    ofstream outFile(file, ios::app | ios::binary);
    if (!outFile.is_open()) throw "File does not exist";
    for (auto &record: vec) {
        outFile.write((char *) &record, sizeof(Alumno));
        outFile<<"\n";
    }
    outFile.close();
}

Alumno FixedRecord::readRecord(int pos){
    ifstream inFile(file, ios::binary);

    Alumno alumno {};

    inFile.seekg(pos * sizeof(Alumno), ios::beg);
    // it works
    string str;
    getline(inFile,str);
    //
    inFile.read((char *) &alumno, sizeof(Alumno));
    inFile.close();

    return alumno;
}

bool FixedRecord::erase(int pos) {

    return false;
}

