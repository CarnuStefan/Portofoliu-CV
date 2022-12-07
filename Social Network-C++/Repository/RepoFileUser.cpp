//
// Created by crnst on 5/20/2022.
//

#include "RepoFileUser.h"
#include <fstream>

using namespace std;

RepoFileUser::RepoFileUser() : ABC<User>() {

}

RepoFileUser::RepoFileUser(const char *filename) {
    this->filename = filename;
    fstream f;
    f.open(this->filename, fstream::in | fstream::out | fstream::app);
    if (f.is_open()) {
        int id;
        f >> id;
        while (!f.eof()) {
            string surname;
            string firstname;
            int varsta;
            f>>ws;
            getline(f, surname);
            getline(f, firstname);
            f>>varsta;
            User ca(id, surname,firstname,varsta);
            RepoFileUser::addItem(ca);
            f >> id >> ws;
        }
    }
    f.close();
}

RepoFileUser::~RepoFileUser() {
    fstream f(this->filename);
    if (f.is_open())
        f.close();
}

void RepoFileUser::save_to_file() {
    ofstream f;
    f.open(this->filename, ios::out);
    if (f.is_open()) {
        vector<User> users = ABC<User>::getAll();
        for (auto &i: users)
            f << i;
        f.close();
    }
}