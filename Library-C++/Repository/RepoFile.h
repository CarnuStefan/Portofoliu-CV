//
// Created by crnst on 5/9/2022.
//

#ifndef LAB9_10_REPOFILE_H
#define LAB9_10_REPOFILE_H


#include "Repo.h"

class RepoFile: public Repo{
private:
    const char* filename{};
public:
    RepoFile();
    explicit RepoFile(const char* filename);
    ~RepoFile();
    void clear_file();
    void save_to_file();
};


#endif //LAB9_10_REPOFILE_H
