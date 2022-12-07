//
// Created by crnst on 5/10/2022.
//

#include "Friendship.h"

Friendship::Friendship() = default;

Friendship::Friendship(int idpr, int idp, const Lista<Message> &conv) {
    this->idprincipal = idpr;
    this->idprieten = idp;
    this->conversatie = conv;
}

Friendship::Friendship(Friendship const &f) {
    this->idprincipal = f.idprincipal;
    this->idprieten = f.idprieten;
    this->conversatie = f.conversatie;
}

int Friendship::getIDPrin() const {
    return this->idprincipal;
}


int Friendship::getIDFriend() const {
    return this->idprieten;
}

Lista<Message> Friendship::getConvo() {
    return this->conversatie;
}

void Friendship::setIDPrin(int idpr) {
    this->idprincipal = idpr;
}

void Friendship::setIDFriend(int idp) {
    this->idprieten = idp;
}

void Friendship::setConvo(const Lista<Message> &conv) {
    this->conversatie = conv;
}

void Friendship::addMessage(const Message &m) {
    this->conversatie.add(m);

}

void Friendship::deleteMessage(int i) {
    for (auto &item: this->conversatie.getAll()) {
        if (item.getId() == i)
            this->conversatie.remove(item);
    }
}

Friendship &Friendship::operator=(const Friendship &f) noexcept {
    if (*this != f) {
        this->idprincipal = f.idprincipal;
        this->idprieten = f.idprieten;
        this->conversatie = f.conversatie;
    }
    return *this;
}

bool Friendship::operator==(const Friendship &f) const {
    return ((this->idprincipal == f.idprincipal) && (this->idprieten == f.idprieten)) ||
           ((this->idprincipal == f.idprieten) && (this->idprieten == f.idprincipal));
}

bool Friendship::operator!=(const Friendship &f) const {
    return ((this->idprincipal != f.idprincipal) && (this->idprieten != f.idprieten)) ||
           ((this->idprincipal != f.idprieten) && (this->idprieten != f.idprincipal));
}

bool Friendship::operator>(Friendship const &f) {
    return (this->conversatie.size() > f.conversatie.size());
}

bool Friendship::operator<(const Friendship &f) {
    return (this->conversatie.size() < f.conversatie.size());
}

Friendship::~Friendship() = default;


