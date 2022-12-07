//
// Created by crnst on 5/9/2022.
//

#include "RepoFile.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

RepoFile::RepoFile() : Repo() {

}

RepoFile::RepoFile(const char *filename) {
    this->filename = filename;
    fstream f;
    f.open(this->filename, fstream::in | fstream::out | fstream::app);
    if (f.is_open()) {
        int cod;
        f >>cod>>ws;
        while (!f.eof()) {
                string temptitlu;
                string tempautor;
                string tempgen;
                int stoc;
                double pret;
                getline(f,temptitlu);
                getline(f,tempautor);
                getline(f,tempgen);
                f >> stoc;
                f >> pret;
                char *titlu = new char[temptitlu.size() + 1];
                char *autor = new char[tempautor.size() + 1];
                char *gen = new char[tempgen.size() + 1];
                strcpy(titlu, temptitlu.c_str());
                strcpy(autor, tempautor.c_str());
                strcpy(gen, tempgen.c_str());
                Carte ca(cod, titlu, autor, gen, stoc, pret);
                delete[] titlu;
                delete[] autor;
                delete[] gen;
                RepoFile::addItem(ca);
                f >> cod >>ws;
            }
        }
        f.close();
    }

RepoFile::~RepoFile() {
    fstream f(this->filename);
    if (f.is_open())
        f.close();
}

void RepoFile::save_to_file() {
    ofstream f;
    f.open(this->filename, ios::out);
    if (f.is_open()) {
        vector<Carte> carti = RepoFile::getAll();
        for (auto &i: carti)
            f << i.getcod() << '\n'
              << i.gettitlu() << '\n'
              << i.getautor() << '\n'
              << i.getgen() << '\n'
              << i.getstoc() << '\n'
              << i.getpret() << '\n';
        f.close();
    }
}

void RepoFile::clear_file() {
    ofstream f;
    f.open(this->filename, std::ofstream::out | std::ofstream::trunc);
    f.close();
}
