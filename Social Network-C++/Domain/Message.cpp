//
// Created by crnst on 5/10/2022.
//

#include "Message.h"
#include <iostream>
using namespace std;

Message::Message() = default;

Message::Message(int id, const string &f, const string &t, const string &text) {
    this->id = id;
    this->from = f;
    this->to = t;
    this->text = text;
}

int Message::getId() {
    return this->id;
}

string Message::getFrom() {
    return this->from;
}

string Message::getTo() {
    return this->to;
}

string Message::getText() {
    return this->text;
}

void Message::setId(int nr) {
    this->id = nr;
}

void Message::setFrom(const string &f) {
    this->from = f;
}

void Message::setTo(const string &t) {
    this->to = t;
}

void Message::setText(const string &tex) {
    this->text = tex;
}

ostream &operator<<(ostream &os, Message &m) {
    os
            << "From: " << m.from <<'\n'
            << "To: " << m.to << '\n'
            << m.text << '\n';
    return os;
}

Message &Message::operator=(Message *m) {
    if (this != m) {
        this->id = m->id;
        this->from = m->from;
        this->to = m->to;
        this->text = m->text;
    }
    return *this;
}

bool Message::operator==(Message &m) {
    return (this->id == m.id) && (this->from == m.from) && (this->to == m.to) && (this->text == m.text);
}

bool Message::operator!=(Message &m) {
    return (this->id != m.id) && (this->from != m.from) && (this->to != m.to) && (this->text != m.text);
}

Message::~Message() = default;
