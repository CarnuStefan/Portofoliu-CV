//
// Created by crnst on 5/20/2022.
//

#include "RepoFileFriendships.h"
#include <fstream>

using namespace std;

RepoFileFriendships::RepoFileFriendships() : Lista<Friendship>() {

}

RepoFileFriendships::RepoFileFriendships(const char *filename) {
    this->filename = filename;
    fstream f;
    f.open(this->filename, fstream::in | fstream::out | fstream::app);
    if (f.is_open()) {
        int idprin;
        f >> idprin;
        while (!f.eof()) {
            int idpriet;
            int size;
            Lista<Message> conv;
            f >> idpriet;
            f >> size;
            for (int i = 0; i < size; ++i) {
                string from;
                string to;
                string text;
                f >> ws;
                getline(f, from);
                getline(f, to);
                getline(f, text);
                Message m(i+1, from, to, text);
                conv.add(m);
            }
            Friendship fr(idprin, idpriet, conv);
            RepoFileFriendships::add(fr);
            f >> idprin;
        }
    }
    f.close();
}

RepoFileFriendships::~RepoFileFriendships() {
    fstream f(this->filename);
    if (f.is_open())
        f.close();
}

void RepoFileFriendships::save_to_file() {
    ofstream f;
    f.open(this->filename, ios::out);
    if (f.is_open()) {
        vector<Friendship> frien = Lista<Friendship>::getAll();
        for (auto &i: frien) {
            f
                    << i.getIDPrin() << '\n'
                    << i.getIDFriend() << '\n'
                    << i.getConvo().size() << '\n';
            for (auto &j: i.getConvo().getAll()) {
                f
                        << j.getFrom() << '\n'
                        << j.getTo() << '\n'
                        << j.getText() << '\n';
            }
        }
        f.close();
    }
}