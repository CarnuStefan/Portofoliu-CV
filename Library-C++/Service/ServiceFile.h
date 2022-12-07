//
// Created by crnst on 5/9/2022.
//
#ifndef LAB9_10_SERVICEFILE_H
#define LAB9_10_SERVICEFILE_H

#include "..\Repository\RepoFile.h"

class ServiceFile {
private:
    RepoFile repo;
public:
    ServiceFile();
    explicit ServiceFile(RepoFile&);
    void add(int c, char *t, char *a, char *g, int s, double p);
    void update(int c, char *nt, char *na, char *ng, int ns, double np);
    void remove(int c);
    void removeAll();
    int size();
    Carte getItem(int cod);
    vector<Carte> getAll();
    vector<Carte> getGen(char* gen);
    bool inRepo(int cod);
    void clearFile();
    ~ServiceFile();
};


#endif //LAB9_10_SERVICEFILE_H
