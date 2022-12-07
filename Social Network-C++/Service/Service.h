//
// Created by crnst on 5/18/2022.
//

#ifndef PROJECT_SERVICE_H
#define PROJECT_SERVICE_H

#include "../TAD/ABC.h"
#include "../Domain/User.h"
#include "../Domain/Friendship.h"
#include "../Repository/RepoFileUser.h"
#include "../Repository/RepoFileFriendships.h"

class Service {
private:
    RepoFileUser repoUser;
    RepoFileFriendships repoFriend;
public:
    Service();

    Service(const RepoFileUser &ru, const RepoFileFriendships &rf);

    void addUser(const string &surname, const string &firstname, int age);

    void addFriendship(int id1, int id2);

    void addMesaj(int idfrom, int idto, const string &text);

    Lista<Message> getConvo(int idfrom, int idto);

    void delMesaj(int idfrom, int idto, int i);

    void delFriendship(int idfrom, int idto);

    void delUser(int id);

    vector<User> getByName(const string &surname);


    User getUser(int id);

    vector<User> getFriends(int id);

    vector<User> getAllUsers();
};


#endif //PROJECT_SERVICE_H
