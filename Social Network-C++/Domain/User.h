//
// Created by crnst on 5/10/2022.
//

#ifndef PROJECT_USER_H
#define PROJECT_USER_H

#include <string>
#include <iostream>
using namespace std;

class User {
private:
    int id{};
    string surname;
    string firstname;
    int age{};
public:
    User();
    User(int n,const string& numefam,const string& prenume,int a);
    ~User();
    int getId() const;
    string getSurname();
    string getFirstname();
    int getAge() const;
    void setId(int nid);
    void setSurname(string);
    void setFirstname(string);
    void setAge(int varsta);
    User& operator=(User *u);
    bool operator==(User& u) const;
    bool operator!=(User& u) const;
    bool operator>(User& u) const;
    bool operator<(User& u) const;
    friend ostream &operator<<(ostream &os,User &u);
};



#endif //PROJECT_USER_H
