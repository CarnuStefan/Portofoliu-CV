//
// Created by crnst on 5/8/2022.
//

#ifndef LAB9_10_UI_H
#define LAB9_10_UI_H

#include "../Service/ServiceFile.h"

class UI {
private:
    ServiceFile serv;
    ServiceFile cos;

    void handle_adauga();

    void handle_adauga_cos();

    void handle_update();

    void handle_sterge();

    void handle_sterge_cos();

    void handle_afisare();

    void handle_afisare_cos();

    void handle_afisare_marime();

    void handle_getbygen();

    void handle_cos();

    void handle_plasare_comanda();

    void handle_golire_cos();

public:
    UI();

    explicit UI(ServiceFile &service, ServiceFile &cos);

    static void showmenu();

    static void showmenuCos();

    void runUI();

    ~UI();
};


#endif //LAB9_10_UI_H
