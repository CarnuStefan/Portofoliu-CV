//
// Created by crnst on 5/5/2022.
//

#include "Carte.h"
#include "cstring"

Carte::Carte() = default;

Carte::~Carte() = default;

Carte::Carte(int c, char *t, char *a, char *g, int s, double p) {
    this->cod = c;
    this->titlu = t;
    this->autor = a;
    this->gen = g;
    this->stoc = s;
    this->pret = p;

}

Carte::Carte(const Carte &ca) {
    this->cod = ca.cod;
    this->titlu = new char[strlen(ca.titlu) + 1];
    strcpy(this->titlu, ca.titlu);
    this->autor = new char[strlen(ca.autor) + 1];
    strcpy(this->autor, ca.autor);
    this->gen = new char[strlen(ca.gen) + 1];
    strcpy(this->gen, ca.gen);
    this->stoc = ca.stoc;
    this->pret = ca.pret;
}

void Carte::setcod(int c) {
    this->cod = c;
}

void Carte::settitlu(char *t) {
    this->titlu = t;
}

void Carte::setautor(char *a) {
    this->autor = a;
}

void Carte::setgen(char *g) {
    this->gen = g;
}

void Carte::setstoc(int s) {
    this->stoc = s;
}

void Carte::setpret(double p) {
    this->pret = p;
}

int Carte::getcod() const {
    return this->cod;
}

char *Carte::gettitlu() {
    return this->titlu;
}

char *Carte::getautor() {
    return this->autor;
}

char *Carte::getgen() {
    return this->gen;
}

int Carte::getstoc() const {
    return this->stoc;
}

double Carte::getpret() const {
    return this->pret;
}

Carte &Carte::operator=(const Carte &ca) {
    if (this != &ca) {
        this->cod = ca.cod;
        this->titlu = new char[strlen(ca.titlu) + 1];
        strcpy(this->titlu, ca.titlu);
        this->autor = new char[strlen(ca.autor) + 1];
        strcpy(this->autor, ca.autor);
        this->gen = new char[strlen(ca.gen) + 1];
        strcpy(this->gen, ca.gen);
        this->stoc = ca.stoc;
        this->pret = ca.pret;
    }
    return *this;
}

bool Carte::operator==(const Carte &ca) {
    return (this->cod == ca.cod &&
            strcmp(this->titlu, ca.titlu) == 0 &&
            strcmp(this->autor, ca.autor) == 0 &&
            strcmp(this->gen, ca.gen) == 0 &&
            this->stoc == ca.stoc &&
            this->pret == ca.pret);
}

bool Carte::operator!=(const Carte &ca) {
    return (this->cod != ca.cod ||
            strcmp(this->titlu, ca.titlu) != 0 ||
            strcmp(this->autor, ca.autor) != 0 ||
            strcmp(this->gen, ca.gen) != 0 ||
            this->stoc != ca.stoc ||
            this->pret != ca.pret);
}

bool Carte::operator<(const Carte &ca) const {
    return this->pret < ca.pret;
}

bool Carte::operator>(const Carte &ca) const {
    return this->pret > ca.pret;
}

ostream &operator<<(ostream &os, Carte &ca) {
    os
            << "ID: "
            << ca.cod
            << "; Titlu: "
            << ca.titlu
            << "; Autor: "
            << ca.autor
            << "; Gen: "
            << ca.gen
            << "; Stoc: "
            << ca.stoc
            << "; Pret: "
            << ca.pret
            << '\n';
    return os;
}

