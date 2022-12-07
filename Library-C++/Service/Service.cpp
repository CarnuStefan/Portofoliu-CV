//
// Created by crnst on 5/8/2022.
//

#include "Service.h"
#include "cstring"
#include "../Exceptions and Validators/MyException.h"

Service::Service() = default;

Service::Service(Repo &repo) {
    this->repo = repo;
}

void Service::add(int c, char *t, char *a, char *g, int s, double p) {
        Carte ca(c, t, a, g, s, p);
        this->repo.addItem(ca);
}

void Service::update(int c, char *nt, char *na, char *ng, int ns, double np) {
        Carte nca(c, nt, na, ng, ns, np);
        this->repo.updateItem(c, nca);
}

void Service::remove(int c) {
        this->repo.removeItem(c);
}

int Service::size() {
    return this->repo.getSize();
}

vector<Carte> Service::getAll() {
    return this->repo.getAll();
}

vector<Carte> Service::getGen(char *gen) {
    vector<Carte> Cartibygen;
    for (auto &i: this->repo.getAll())
        if (strcmp(i.getgen(), gen) == 0)
            Cartibygen.push_back(i);
    return Cartibygen;
}

Service::~Service() = default;
