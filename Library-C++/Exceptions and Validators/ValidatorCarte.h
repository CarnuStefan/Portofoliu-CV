//
// Created by crnst on 5/19/2022.
//

#ifndef LAB9_10_VALIDATORCARTE_H
#define LAB9_10_VALIDATORCARTE_H


#include <vector>
#include "../Domain/Carte.h"

class ValidatorCarte {
private:
    int errnum{};
    string errmsg;
public:
    ValidatorCarte();
    void validate(char *t, char *a, char *g, string s, string p);
    ~ValidatorCarte();
};


#endif //LAB9_10_VALIDATORCARTE_H
