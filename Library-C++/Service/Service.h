//
// Created by crnst on 5/8/2022.
//

#ifndef LAB9_10_SERVICE_H
#define LAB9_10_SERVICE_H

#include "..\Repository\Repo.h"

class Service {
private:
    Repo repo;
public:
    Service();
    explicit Service(Repo&);
    void add(int c, char *t, char *a, char *g, int s, double p);
    void update(int c, char *nt, char *na, char *ng, int ns, double np);
    void remove(int c);
    int size();
    vector<Carte> getAll();
    vector<Carte> getGen(char* gen);
    ~Service();
};


#endif //LAB9_10_SERVICE_H
