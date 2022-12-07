//
// Created by crnst on 5/8/2022.
//

#include "UI.h"
#include "../Exceptions and Validators/MyException.h"
#include "../Exceptions and Validators/ValidatorCarte.h"
#include <cstring>

UI::UI() = default;

UI::UI(ServiceFile &service, ServiceFile &cos) {
    this->serv = service;
    this->cos = cos;
}

void UI::handle_adauga() {
    int cod;
    string temptitle;
    string tempautor;
    string tempgen;
    string stoc;
    string pret;
    cout << "Da-ti cod-ul:\n";
    cin >> cod;
    cout << "Da-ti titlu:\n";
    cin >> ws;
    getline(cin, temptitle);
    char *titlu = new char[temptitle.size() + 1];
    strcpy(titlu, temptitle.c_str());
    cout << "Da-ti autorul:\n";
    cin >> ws;
    getline(cin, tempautor);
    char *autor = new char[tempautor.size() + 1];
    strcpy(autor, tempautor.c_str());
    cout << "Da-ti genul:\n";
    cin >> ws;
    getline(cin, tempgen);
    char *gen = new char[tempautor.size() + 1];
    strcpy(gen, tempgen.c_str());
    cout << "Da-ti stocul:\n";
    cin >> ws;
    getline(cin,stoc);
    cout << "Da-ti pretul:\n";
    cin >> ws;
    getline(cin,pret);
    try {
        ValidatorCarte val;
        val.validate(titlu, autor, gen, stoc, pret);
        int stock= stoi(stoc);
        double price= stod(pret);
        this->serv.add(cod, titlu, autor, gen, stock, price);
    }
    catch (MyException &e) {
        cout << e.what();
    }

    delete[] titlu;
    delete[] autor;
    delete[] gen;

}

void UI::handle_update() {
    int cod;
    string temptitle;
    string tempautor;
    string tempgen;
    string nstoc;
    string npret;
    cout << "Da-ti codul cartii de actualizat:\n";
    cin >> cod;
    cout << "Da-ti noul titlu:\n";
    cin >> ws;
    getline(cin, temptitle);
    char *ntitlu = new char[temptitle.size() + 1];
    strcpy(ntitlu, temptitle.c_str());
    cout << "Da-ti noul autor:\n";
    cin >> ws;
    getline(cin, tempautor);
    char *nautor = new char[tempautor.size() + 1];
    strcpy(nautor, tempautor.c_str());
    cout << "Da-ti noul gen:\n";
    cin >> ws;
    getline(cin, tempgen);
    char *ngen = new char[tempautor.size() + 1];
    strcpy(ngen, tempgen.c_str());
    cout << "Da-ti noul stoc\n";
    cin >> ws;
    getline(cin,nstoc);
    cout << "Da-ti noul pret:\n";
    cin >> ws;
    getline(cin,npret);
    try {
        ValidatorCarte val;
        val.validate(ntitlu, nautor, ngen, nstoc, npret);
        int stock= stoi(nstoc);
        double price= stod(npret);
        this->serv.update(cod,ntitlu, nautor, ngen, stock, price);
    }
    catch (MyException &e) {
        cout << e.what();
    }
    delete[] ntitlu;
    delete[] nautor;
    delete[] ngen;

}

void UI::handle_sterge() {
    cout << "Dati cod-ul cartii de sters:\n";
    int cod;
    cin >> cod;
    try {
        this->serv.remove(cod);
    }
    catch (MyException &e)
    {
        cout<<e.what();
    }
}

void UI::handle_afisare() {
    vector<Carte> entities = this->serv.getAll();
    for (auto &entitie: entities)
        cout << entitie;
}

void UI::handle_afisare_marime() {
    cout << this->serv.size();
}

void UI::showmenu() {
    cout << "Meniu\n"
         << "1. Adaugare carte\n"
         << "2. Modificare carte\n"
         << "3. Stergere carte\n"
         << "4. Afisare toate cartile\n"
         << "5. Afisare total carti\n"
         << "6. Afisare dupa gen\n"
         << "7. Submeniu cos\n"
         << "x. Exit\n";
}

void UI::runUI() {
    char op;
    while (true) {
        showmenu();
        cout << "Dati optiunea:";
        cin >> op;
        switch (op) {
            case '1':
                handle_adauga();
                break;
            case '2':
                handle_update();
                break;
            case '3':
                handle_sterge();
                break;
            case '4':
                handle_afisare();
                break;
            case '5':
                handle_afisare_marime();
                break;
            case '6':
                handle_getbygen();
                break;
            case '7':
                handle_cos();
                break;
            case 'x':
                return;
            default:
                cout << "Optiune gresita! Reincercati!\n" << endl;
        }
    }
}

void UI::handle_getbygen() {
    cout << "Da-ti genul:\n";
    string tempgen;
    cin >> ws;
    getline(cin, tempgen);
    char *gen = new char[tempgen.size()];
    strcpy(gen, tempgen.c_str());
    vector<Carte> gotbygen = serv.getGen(gen);
    for (auto &i: gotbygen) {
        cout << i << '\n';
    }
    delete[] gen;
}

void UI::showmenuCos() {
    cout << "Meniu Cos\n"
         << "1. Adaugare carte in cos\n"
         << "2. Scoatere carte din cos\n"
         << "3. Afisare toate cartile din cos\n"
         << "4. Sterge toate cartile din cos\n"
         << "5. Plasare comanda\n"
         << "x. Exit\n";
}

void UI::handle_cos() {
    char opc;
    while (true) {
        showmenuCos();
        cout << "Dati optiunea:";
        cin >> opc;
        switch (opc) {
            case '1':
                handle_adauga_cos();
                break;
            case '2':
                handle_sterge_cos();
                break;
            case '3':
                handle_afisare_cos();
                break;
            case '4':
                handle_golire_cos();
                break;
            case '5':
                handle_plasare_comanda();
                break;
            case 'x':
                return;
            default:
                cout << "Optiune gresita! Reincercati!\n" << endl;
        }
    }
}

void UI::handle_adauga_cos() {
    handle_afisare();
    int cod;
    int stoc;
    cout << "Da-ti cod-ul cartii:\n";
    cin >> cod;
    cout << "Da-ti numarul de bucati:\n";
    cin >> stoc;
    if (this->serv.inRepo(cod)) {
        Carte cas = this->serv.getItem(cod);
        if (cas.getstoc() >= stoc && stoc > 0) {
            if (this->cos.inRepo(cod)) {
                Carte ca = this->cos.getItem(cod);
                this->cos.update(cod, cas.gettitlu(), cas.getautor(), cas.getgen(), ca.getstoc()+stoc, cas.getpret());
                this->serv.update(cas.getcod(), cas.gettitlu(), cas.getautor(), cas.getgen(), cas.getstoc() - stoc,
                                  cas.getpret());
            } else {
                this->cos.add(cod, cas.gettitlu(), cas.getautor(), cas.getgen(), stoc, cas.getpret());
                this->serv.update(cas.getcod(), cas.gettitlu(), cas.getautor(), cas.getgen(), cas.getstoc() - stoc,
                                  cas.getpret());
            }
        } else
            cout << "Nu putem adauga mai mult de " << cas.getstoc() << " carti cu codul " << cas.getcod() << "in cos\n";
    } else cout << "Cartea nu exista in librarie\n";
}

void UI::handle_sterge_cos() {
    handle_afisare_cos();
    int cod;
    int stoc;
    cout << "Da-ti cod-ul cartii de scos:\n";
    cin >> cod;
    cout << "Da-ti numarul de bucati care trebuie scoase:\n";
    cin >> stoc;
    if (this->cos.inRepo(cod)) {
        Carte ca = this->cos.getItem(cod);
        Carte cas = this->serv.getItem(cod);
        if (ca.getstoc() > stoc && stoc > 0) {
            this->cos.update(cod, ca.gettitlu(), ca.getautor(), ca.getgen(), ca.getstoc() - stoc, ca.getpret());
            this->serv.update(cas.getcod(), cas.gettitlu(), cas.getautor(), cas.getgen(), cas.getstoc() + stoc,
                              cas.getpret());
        } else if (ca.getstoc() == stoc && stoc > 0) {
            this->cos.remove(cod);
            this->serv.update(cas.getcod(), cas.gettitlu(), cas.getautor(), cas.getgen(), cas.getstoc() + stoc,
                              cas.getpret());
        } else
            cout << "Nu putem scoate mai mult de " << ca.getstoc() << " carti cu codul " << ca.getcod() << "din cos\n";
    } else cout << "Cartea nu este in cos\n";
}

void UI::handle_afisare_cos() {
    vector<Carte> entities = this->cos.getAll();
    for (auto &entitie: entities)
        cout << entitie << endl;
}

void UI::handle_plasare_comanda() {
    vector<Carte> comanda = this->cos.getAll();
    double total = 0;
    int dez = 0, art = 0, fic = 0, disc1 = 0, disc2 = 0;
    for (auto &item: comanda) {
        total += (item.getpret() * item.getstoc());
        if (strcmp(item.getgen(), "dezvoltare personala") == 0)
            dez += item.getstoc();
        if (strcmp(item.getgen(), "fictiune") == 0)
            fic += item.getstoc();
        if (strcmp(item.getgen(), "arta") == 0)
            art += item.getstoc();
    }
    if (dez >= 2)
        disc1 = 15;
    if (art >= 1 && fic >= 1)
        disc2 = 18;
    total -= ((disc1 * total) / 100);
    total -= ((disc2 * total) / 100);
    handle_afisare_cos();
    cout << "Totalul este " << total;
    if (disc1)
        cout << "(discountul 'DEZVOLTARE' este aplicat)\n";
    if (disc2)
        cout << "(discountul 'ARTA SI FICTIUNE' este aplicat)\n";
    cout << "\n";
    this->cos.removeAll();
    this->cos.clearFile();
}

void UI::handle_golire_cos() {
    char ok;
    cout << "Goliti cosul?Y/N\n";
    cin >> ok;
    if (ok == 'y' || ok == 'Y') {
        for (auto &i: this->cos.getAll()) {
            Carte cas = this->serv.getItem(i.getcod());
            this->serv.update(i.getcod(), i.gettitlu(), i.getautor(), i.getgen(), i.getstoc() + cas.getstoc(),
                              i.getpret());
        }
        this->cos.removeAll();
    }

}

UI::~UI() = default;