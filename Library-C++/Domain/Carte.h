//
// Created by crnst on 5/5/2022.
//

#ifndef LAB9_10_CARTE_H
#define LAB9_10_CARTE_H
#include <iostream>
using namespace std;

class Carte {
private:
    int cod{};
    char *titlu{};
    char *autor{};
    char *gen{};
    int stoc{};
    double pret{};
public:
    Carte();

    Carte(int c, char *t, char *a, char *g, int s, double p);

    Carte(const Carte &ca);

    ~Carte();

    void setcod(int);

    void settitlu(char *);

    void setautor(char *);

    void setgen(char *);

    void setstoc(int);

    void setpret(double);

    int getcod() const;

    char *gettitlu();

    char *getautor();

    char *getgen();

    int getstoc() const;

    double getpret() const;

    Carte &operator=(const Carte &ca);

    bool operator==(const Carte &ca);

    bool operator!=(const Carte &ca);

    bool operator<(const Carte &ca) const;

    bool operator>(const Carte &ca) const;

    friend ostream& operator<<(ostream&os, Carte&ca);

};


#endif //LAB9_10_CARTE_H
