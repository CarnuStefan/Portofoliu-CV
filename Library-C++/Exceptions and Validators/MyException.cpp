//
// Created by crnst on 5/19/2022.
//

#include "MyException.h"

#include <utility>


MyException::MyException()
{
    this->mesaj = "";
}

MyException::MyException(string mesaj_)
{
    this->mesaj = std::move(mesaj_);
}

const char* MyException::what() const noexcept
{
    return this->mesaj.c_str();
}
