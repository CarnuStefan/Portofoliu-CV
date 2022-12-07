//
// Created by crnst on 5/19/2022.
//

#ifndef LAB9_10_MYEXCEPTION_H
#define LAB9_10_MYEXCEPTION_H
#include <exception>
#include <string>
using namespace std;

class MyException : public exception {
protected:
    string mesaj;

public:
    MyException();
    explicit MyException(string mesaj_);
    ~MyException() override = default;

    const char* what() const noexcept override;
};


#endif //LAB9_10_MYEXCEPTION_H
