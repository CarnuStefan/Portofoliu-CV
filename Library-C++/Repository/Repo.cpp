//
// Created by crnst on 5/5/2022.
//

#include "Repo.h"
#include "algorithm"
#include "../Exceptions and Validators/ValidatorCarte.h"
#include "../Exceptions and Validators/MyException.h"

void Repo::addItem(Carte &ca) {
    for (auto &item:repo) {
        if (ca.getcod()==item.getcod())
        {
            throw MyException("Eroare: Exista deja o carte cu acest cod in librarie;\n");
        }
    }
    this->repo.push_back(ca);

}

std::vector<Carte> Repo::getAll() {
    return this->repo;
}

void Repo::updateItem(int cod, Carte &ca) {
    int ok=0;
    for (auto &item:repo) {
        if (ca.getcod()==item.getcod())
        {
            ok=1;
        }
    }
    if (!ok)
    {
        throw MyException("Eroare: Nu exista o carte cu acest cod in librarie;\n");
    }
    for (auto &i: repo)
        if (cod == i.getcod())
            i = ca;
}

void Repo::removeItem(int &ca) {
    int ok=0;
    Carte to_del;
    for (auto &Item: repo)
        if (ca == Item.getcod())
        {
            ok=1;
            to_del=Item;
        }
    if (ok) {
        auto iter = find(repo.begin(), repo.end(), to_del);
        if (iter != repo.end())
            repo.erase(iter);
    }
    else throw MyException("Eroare: Cartea de sters nu exista!\n");
}

Carte Repo::getItem(int cod) {
    for (auto &i: repo)
        if (cod == i.getcod())
            return i;
    return {};
}

int Repo::getSize() {
    return int(repo.size());
}

bool Repo::inRepo(int cod) {
    for (auto &i: repo)
        if (cod == i.getcod())
            return true;
    return false;
}

Repo::Repo() = default;

Repo::~Repo() = default;
