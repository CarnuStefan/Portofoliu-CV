//
// Created by crnst on 5/22/2022.
//

#ifndef PROJECT_UI_H
#define PROJECT_UI_H


#include "../Service/Service.h"
#include <iostream>
class UI {
private:
    Service serv;
    static void showmenu();
public:
    UI();
    explicit UI(const Service& s);
    void runUI();


    void handle_users();

    static void showmenuUser();

    void handle_users_add();

    void handle_users_delete();

    void handle_users_showall();

    void handle_friends();

    static void showmenuFriendship();

    void handle_friends_add();

    void handle_friends_delete();

    void handle_friends_show();

    void handle_messages();

    static void showmenuMessages();

    void handle_messages_add();

    void handle_messages_delete();

    void handle_messages_show();

    ~UI();
};


#endif //PROJECT_UI_H
