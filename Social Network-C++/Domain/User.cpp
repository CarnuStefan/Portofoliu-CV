//
// Created by crnst on 5/10/2022.
//

#include "User.h"
#include <utility>

using namespace std;

User::User() = default;

User::User(int n, const string &numefam, const string &prenume, int a) {
    this->id = n;
    this->surname = numefam;
    this->firstname = prenume;
    this->age = a;
}

User::~User() = default;

int User::getId() const {
    return this->id;
}

string User::getSurname() {
    return this->surname;
}

string User::getFirstname() {
    return this->firstname;
}

int User::getAge() const {
    return this->age;
}

void User::setId(int nid) {
    this->id = nid;
}

void User::setSurname(string nume) {
    this->surname = std::move(nume);
}

void User::setFirstname(string nume) {
    this->firstname = std::move(nume);
}

void User::setAge(int varsta) {
    this->age = varsta;
}

User &User::operator=(User *u) {
    if (this != u) {
        this->id = u->id;
        this->surname = u->surname;
        this->firstname = u->firstname;
        this->age = u->age;
    }
    return *this;
}

bool User::operator==(User &u) const {
    return this->id == u.id;
}

bool User::operator!=(User &u) const {
    return this->id != u.id;
}

bool User::operator>(User &u) const {
    return this->id > u.id;
}

bool User::operator<(User &u) const {
    return this->id < u.id;
}

ostream &operator<<(ostream &os,User &u) {
    os
            << u.getId() << '\n'
            << u.getSurname() << '\n'
            << u.getFirstname() << '\n'
            << u.getAge() << '\n';
    return os;
}