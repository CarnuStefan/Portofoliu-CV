//
// Created by crnst on 5/22/2022.
//

#include "UI.h"
#include <iostream>

using namespace std;

UI::UI() = default;

UI::UI(const Service &s) {
this->serv=s;
}


void UI::showmenu() {
    cout << "\n-Meniu Principal-\n"
         << "1.Submeniu utilizatori\n"
         << "2.Submeniu prietenii\n"
         << "3.Submeniu conversatii\n"
         << "x.Exit\n";
}

void UI::runUI() {
    char op;
    while (true) {
        showmenu();
        cout << "Da-ti optiunea: ";
        cin >> op;
        switch (op) {
            case '1':
                handle_users();
                break;
            case '2':
                handle_friends();
                break;
            case '3':
                handle_messages();
                break;
            case 'x':
                return;
            default:
                cout << "Optiune invalida!\n";

        }

    }
}

void UI::showmenuUser() {
    cout << "\n-Submeniu Utilizatori-\n"
         << "1.Adauga utilizator\n"
         << "2.Sterge utilizator\n"
         << "3.Afisare utilizatori\n"
         << "x.Exit\n";
}

void UI::handle_users() {
    char opu;
    while (true) {
        showmenuUser();
        cout << "Da-ti optiunea:";
        cin >> opu;
        switch (opu) {
            case '1':
                handle_users_showall();
                handle_users_add();
                break;
            case '2':
                handle_users_showall();
                handle_users_delete();
                break;
            case '3':
                handle_users_showall();
                break;
            case 'x':
                return;
            default:
                cout << "Optiune invalida!\n";
        }
    }
}

void UI::handle_users_add() {
    string surname;
    string firstname;
    int age;
    cout << "Numele de familie: ";
    cin >> ws;
    getline(cin, surname);
    cout << "Prenumele: ";
    cin >> ws;
    getline(cin, firstname);
    cout << "Varsta: ";
    cin >> age;
    serv.addUser(surname, firstname, age);
}

void UI::handle_users_delete() {
    string surname;
    cout << "Numele de familie: ";
    cin >> ws;
    getline(cin, surname);
    vector<User> named = serv.getByName(surname);
    for (auto &i: named) {
        cout << i<<'\n';
    }
    int to_del;
    cout << "Da-ti idul utilizatorului care trebuie sters: ";
    cin >> to_del;
    serv.delUser(to_del);
}

void UI::handle_users_showall() {
    vector<User> users = serv.getAllUsers();
    for (auto &item: users) {
        cout << item.getSurname() << ' ' << item.getFirstname() << " Varsta:" << item.getAge() << '\n';
    }
}


void UI::showmenuFriendship() {
    cout << "\n-Submeniu prietenie-\n"
         << "1.Adauga prietenie\n"
         << "2.Sterge prietenie\n"
         << "3.Afisare prietenii unui utilizator\n"
         << "x.Exit\n";
}

void UI::handle_friends() {
    char opf;
    while (true) {
        showmenuFriendship();
        cout << "Da-ti optiunea:";
        cin >> opf;
        switch (opf) {
            case '1':
                handle_users_showall();
                handle_friends_add();
                break;
            case '2':
                handle_users_showall();
                handle_friends_delete();
                break;
            case '3':
                handle_users_showall();
                handle_friends_show();
                break;
            case 'x':
                return;
            default:
                cout << "Optiune invalida!\n";
        }
    }
}

void UI::handle_friends_add() {
    int id1;
    int id2;
    string surname1;
    string surname2;
    cout << "Alegeti primul utilizator\n" << "Numele de familie: ";
    cin >> ws;
    getline(cin, surname1);
    vector<User> named = serv.getByName(surname1);
    for (auto &i: named) {
        cout << i<<'\n';
    }
    cout << "ID: ";
    cin >> id1;
    cout << "Alegeti al doilea utilizator\n" << "Numele de familie: ";
    cin >> ws;
    getline(cin, surname2);
    named = serv.getByName(surname2);
    for (auto &i: named) {
        cout << i<<'\n';
    }
    cout << "ID: ";
    cin >> id2;
    serv.addFriendship(id1, id2);
}

void UI::handle_friends_delete() {
    int id1;
    int id2;
    string surname;
    cout << "Alegeti primul utilizator\n" << "Numele de familie: ";
    cin >> ws;
    getline(cin, surname);
    vector<User> named = serv.getByName(surname);
    for (auto &i: named) {
        cout << i<<'\n';
    }
    cout << "ID: ";
    cin >> id1;
    vector<User> friends = serv.getFriends(id1);
    if (!friends.empty()) {
        for (auto &item: friends) {
            cout << item<<'\n';
        }
        cout << "Da-ti id-ul prietenului care trebuie sters: ";
        cin >> id2;
        serv.delFriendship(id1, id2);
    } else cout << "Nu exista prietenii\n";
}

void UI::handle_friends_show() {
    int id;
    string surname;
    cout << "Alegeti utilizatorul ai carui prieteni doriti sa ii vedeti\n" << "Numele de familie: ";
    cin >> ws;
    getline(cin, surname);
    vector<User> named = serv.getByName(surname);
    for (auto &i: named) {
        cout << i<<'\n';
    }
    cout << "ID: ";
    cin >> id;
    vector<User> friends = serv.getFriends(id);
    if (!friends.empty()) {
        for (auto &item: friends) {
            cout << item.getSurname() << ' ' << item.getFirstname() << " Varsta:" << item.getAge() << '\n';
        }
    } else cout << "Nu exista prieteni\n";
}

void UI::showmenuMessages() {
    cout << "\n-Submeniu conversatii-\n"
         << "1.Adauga mesaj\n"
         << "2.Sterge mesaj\n"
         << "3.Afisare conversatie\n"
         << "x.Exit\n";
}

void UI::handle_messages() {
    char opm;
    while (true) {
        showmenuMessages();
        cout << "Da-ti optiunea:";
        cin >> opm;
        switch (opm) {
            case '1':
                handle_users_showall();
                handle_messages_add();
                break;
            case '2':
                handle_users_showall();
                handle_messages_delete();
                break;
            case '3':
                handle_users_showall();
                handle_messages_show();
                break;
            case 'x':
                return;
            default:
                cout << "Optiune invalida!\n";
        }
    }
}

void UI::handle_messages_add() {
    int id1;
    int id2;
    string surname1;
    string text;
    cout << "Alegeti primul utilizator\n" << "Numele de familie: ";
    cin >> ws;
    getline(cin, surname1);
    vector<User> named = serv.getByName(surname1);
    for (auto &i: named) {
        cout << i<<'\n';
    }
    cout << "ID: ";
    cin >> id1;
    vector<User> friends = serv.getFriends(id1);
    if (!friends.empty()) {
        for (auto &item: friends) {
            cout << item<<'\n';
        }
        cout << "Alegeti al doilea utilizator\n";
        cout << "ID: ";
        cin >> id2;
        Lista<Message> conv = serv.getConvo(id1, id2);
        if (conv.size()) {
            for (int i = 0; i < conv.size(); ++i) {
                Message m = conv[i];
                cout << m << '\n';
            }
        }
        cout << "Scrieti mesajul:\n";
        cin >> ws;
        getline(cin, text);
        serv.addMesaj(id1, id2, text);
    } else cout << "Nu exista prieteni\n";}

void UI::handle_messages_delete() {
    int id1;
    int id2;
    int idmes;
    string surname;
    cout << "Alegeti primul utilizator\n" << "Numele de familie: ";
    cin >> ws;
    getline(cin, surname);
    vector<User> named = serv.getByName(surname);
    for (auto &i: named) {
        cout << i;
    }
    cout << "ID: ";
    cin >> id1;
    vector<User> friends = serv.getFriends(id1);
    for (auto &item: friends) {
        cout << item<<'\n';
    }
    cout << "Da-ti id-ul prietenului: ";
    cin >> id2;
    Lista<Message> conv = serv.getConvo(id1, id2);
    if (conv.size()) {
        for (int i = 0; i < conv.size(); ++i) {
            Message m = conv[i];
            cout << m.getId() << '\n' << m << '\n';
        }
        cout << "Da-ti id-ul mesajului de sters: ";
        cin >> idmes;
        serv.delMesaj(id1, id2, idmes);
    } else {
        cout << "Nu exista mesaje de sters!\n";
    }
}

void UI::handle_messages_show() {
    int id1;
    int id2;
    string surname;
    cout << "Alegeti primul utilizator\n" << "Numele de familie: ";
    cin >> ws;
    getline(cin, surname);
    vector<User> named = serv.getByName(surname);
    for (auto &i: named) {
        cout << i<<'\n';
    }
    cout << "ID: ";
    cin >> id1;
    vector<User> friends = serv.getFriends(id1);
    if (!friends.empty()) {
        for (auto &item: friends) {
            cout << item<<'\n';
        }
        cout << "Da-ti id-ul prietenului: ";
        cin >> id2;
        Lista<Message> conv = serv.getConvo(id1, id2);
        if (conv.size()) {
            for (int i = 0; i < conv.size(); ++i) {
                Message m = conv[i];
                cout << m << '\n';
            }
        } else cout << "Nu exista mesaje\n";
    } else cout << "Nu exista prieteni\n";
}

UI::~UI() = default;
