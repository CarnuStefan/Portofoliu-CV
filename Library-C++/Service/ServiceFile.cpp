
#include "ServiceFile.h"

#include "cstring"
#include "../Exceptions and Validators/MyException.h"

ServiceFile::ServiceFile() = default;

ServiceFile::ServiceFile(RepoFile &repo) {
    this->repo = repo;
}

void ServiceFile::add(int c, char *t, char *a, char *g, int s, double p) {
        Carte ca(c, t, a, g, s, p);
        this->repo.addItem(ca);
        this->repo.save_to_file();
}

void ServiceFile::update(int c, char *nt, char *na, char *ng, int ns, double np) {
        Carte nca(c, nt, na, ng, ns, np);
        this->repo.updateItem(c, nca);
        this->repo.save_to_file();
}

void ServiceFile::remove(int c) {
        this->repo.removeItem(c);
        this->repo.save_to_file();
}

void ServiceFile::removeAll() {
    vector<Carte> Items = this->repo.getAll();
    for (auto &Item: Items) {
        int todel=Item.getcod();
        this->repo.removeItem(todel);
    }
    this->repo.clear_file();
}

int ServiceFile::size() {
    return this->repo.getSize();
}

Carte ServiceFile::getItem(int cod) {
    return this->repo.getItem(cod);
}

vector<Carte> ServiceFile::getAll() {
    return this->repo.getAll();
}

vector<Carte> ServiceFile::getGen(char *gen) {
    vector<Carte> Cartibygen;
    for (auto &i: this->repo.getAll())
        if (strcmp(i.getgen(), gen) == 0)
            Cartibygen.push_back(i);
    return Cartibygen;
}

bool ServiceFile::inRepo(int cod) {
    return this->repo.inRepo(cod);
}

void ServiceFile::clearFile() {
    this->repo.clear_file();
}

ServiceFile::~ServiceFile() = default;
