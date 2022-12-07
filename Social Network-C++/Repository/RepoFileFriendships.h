//
// Created by crnst on 5/20/2022.
//

#ifndef PROJECT_REPOFILEFRIENDSHIPS_H
#define PROJECT_REPOFILEFRIENDSHIPS_H


#include "../Domain/Friendship.h"

class RepoFileFriendships: public Lista<Friendship> {
private:
    const char* filename{};
public:
    RepoFileFriendships();
    explicit RepoFileFriendships(const char* filename);
    ~RepoFileFriendships();
    void save_to_file();
};


#endif //PROJECT_REPOFILEFRIENDSHIPS_H
