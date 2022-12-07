//
// Created by crnst on 5/18/2022.
//

#include "Service.h"
#include <random>

Service::Service() = default;

Service::Service(const RepoFileUser &ru, const RepoFileFriendships &rf) {
    this->repoUser = ru;
    this->repoFriend = rf;
}

void Service::addUser(const string &surname, const string &firstname, int age) {
    vector<User> users = repoUser.getAll();
    int id;
    random_device randomEngine;
    uniform_int_distribution<int> intDistro(1, 1000);
    id = intDistro(randomEngine);
    for (auto &item: users) {
        while (id == item.getId()) {
            id = intDistro(randomEngine);
        }
    }
    User u(id, surname, firstname, age);
    repoUser.addItem(u);
    repoUser.save_to_file();
}

void Service::addFriendship(int id1, int id2) {
    Lista<Message> conv;
    Friendship fr(id1, id2, conv);
    repoFriend.add(fr);
    repoFriend.save_to_file();
}

void Service::addMesaj(int idfrom, int idto, const string &text) {
    Lista<Message> conv;
    Friendship fr(idfrom, idto, conv);
    int i = repoFriend.getpos(fr);
    User from = getUser(idfrom);
    User to = getUser(idto);
    vector<Friendship> frs = repoFriend.getAll();
    int id;
    random_device randomEngine;
    uniform_int_distribution<int> intDistro(1, 1000);
    id = intDistro(randomEngine);
    Message m(id, from.getFirstname(), to.getFirstname(), text);
    frs[i].addMessage(m);
    repoFriend.update(frs[i]);
    repoFriend.save_to_file();
}

Lista<Message> Service::getConvo(int idfrom, int idto) {
    Lista<Message> conv;
    Friendship fr(idfrom, idto, conv);
    int pos = repoFriend.getpos(fr);
    vector<Friendship> frs = repoFriend.getAll();
    return frs[pos].getConvo();
}

void Service::delMesaj(int idfrom, int idto, int i) {
    Lista<Message> conv;
    Friendship fr(idfrom, idto, conv);
    int pos = repoFriend.getpos(fr);
    vector<Friendship> frs = repoFriend.getAll();
    frs[pos].deleteMessage(i);
    repoFriend.update(frs[pos]);
    repoFriend.save_to_file();
}

void Service::delFriendship(int idfrom, int idto) {
    Lista<Message> conv;
    Friendship fr(idfrom, idto, conv);
    repoFriend.remove(fr);
    repoFriend.save_to_file();
}

vector<User> Service::getByName(const string &surname) {
    vector<User> result;
    vector<User> users = repoUser.getAll();
    for (auto &item: users)
        if (item.getSurname() == surname) {
            result.push_back(item);
        }
    return result;
}

void Service::delUser(int id) {
    vector<User> users = repoUser.getAll();
    vector<Friendship> frs = repoFriend.getAll();
    for (auto &item: users) {
        if (item.getId() == id)
            repoUser.delItem(item);
    }
    for (auto &item: frs) {
        if (item.getIDPrin() == id || item.getIDFriend() == id) {
            repoFriend.remove(item);
        }
    }
    repoUser.save_to_file();
    repoFriend.save_to_file();
}

User Service::getUser(int id) {
    vector<User> users = repoUser.getAll();
    for (auto &item: users) {
        if (item.getId() == id)
            return item;
    }
    return {};
}

vector<User> Service::getAllUsers() {
    return repoUser.getAll();
}

vector<User> Service::getFriends(int id) {
    vector<User> result;
    vector<Friendship> friends = repoFriend.getAll();
    for (auto &i: friends) {
        if (i.getIDPrin() == id)
            result.push_back(getUser(i.getIDFriend()));
        else if (i.getIDFriend() == id)
            result.push_back(getUser(i.getIDPrin()));
    }
    return result;
}
