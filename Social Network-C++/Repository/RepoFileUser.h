//
// Created by crnst on 5/20/2022.
//

#ifndef PROJECT_REPOFILEUSER_H
#define PROJECT_REPOFILEUSER_H


#include "../TAD/ABC.h"
#include "../Domain/User.h"

class RepoFileUser : public ABC<User> {
private:
    const char* filename{};
public:
    RepoFileUser();
    explicit RepoFileUser(const char* filename);
    ~RepoFileUser();
    void save_to_file();
};


#endif //PROJECT_REPOFILEUSER_H
