//
// Created by crnst on 5/19/2022.
//

#include "ValidatorCarte.h"
#include "MyException.h"

ValidatorCarte::ValidatorCarte() = default;

void ValidatorCarte::validate( char *t, char *a, char *g, string s, string p) {
    string tempautor=a;
    string temptitlu=t;
    string tempgen=g;
    if (tempautor.empty())
    {
        this->errnum++;
        this->errmsg += "Eroare:Autorul este nul!\n";
    }
    if (temptitlu.empty())
    {
        this->errnum++;
        this->errmsg += "Eroare:Titlul este nul!\n";
    }
    if (tempgen.empty())
    {
        this->errnum++;
        this->errmsg += "Eroare:Genul trebuie precizat\n";
    }

    for(char & i : tempautor)
        if (!isalpha(i) && i != ' ')
        {
            this->errnum++;
            this->errmsg += "Eroare:Numele autorului contine caractere nepermise!\n";
            break;
        }

    int st;
    double pr;
    bool numok= true;

    try {
     st= stoi(s);
    }
    catch (invalid_argument &err) {
        this->errnum++;
        this->errmsg+="Eroare:Stocul trebuie sa fie numar intreg\n";
        numok= false;
    }
    try {
        pr= stod(p);
    }
    catch (invalid_argument &err) {
        this->errnum++;
        this->errmsg+="Eroare:Pretul trebuie sa fie numar real\n";
        numok= false;
    }

    if (numok)
    {
        if (st<0)
        {
            this->errnum++;
            this->errmsg+="Eroare:Stocul trebuie sa fie numar pozitiv\n";
        }

        if (pr<0)
        {
            this->errnum++;
            this->errmsg+="Eroare:Pretul trebuie sa fie numar pozitiv\n";
        }
    }

    if (this->errnum)
    {
        throw MyException(errmsg);
    }

}

ValidatorCarte::~ValidatorCarte() = default;
