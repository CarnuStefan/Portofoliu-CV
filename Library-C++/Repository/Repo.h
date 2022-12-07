//
// Created by crnst on 5/5/2022.
//

#ifndef LAB9_10_REPO_H
#define LAB9_10_REPO_H

#include "../Domain/Carte.h"
#include "vector"


class Repo {
private:
    std::vector<Carte> repo;
public:
    Repo();
    ~Repo();
    void addItem(Carte&ca);
    void updateItem(int cod, Carte&ca);
    void removeItem(int&ca);
    Carte getItem(int cod);
    std::vector<Carte> getAll();
    int getSize();
    bool inRepo(int cod);
};


#endif //LAB9_10_REPO_H
