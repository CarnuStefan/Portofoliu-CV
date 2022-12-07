//
// Created by crnst on 5/10/2022.
//

#ifndef PROJECT_MESSAGE_H
#define PROJECT_MESSAGE_H

#include "string"
using namespace std;
class Message {
private:
    int id{};
    string from;
    string to;
    string text;
public:
    Message();
    Message(int id,const string& f, const string& t, const string& text);
    ~Message();
    int getId();
    string getFrom();
    string getTo();
    string getText();
    void setId(int nr);
    void setFrom(const string& f);
    void setTo(const string& t);
    void setText(const string& tex);
    Message& operator=(Message *m);
    bool operator==(Message& m);
    bool operator!=(Message& m);
    friend ostream& operator<<(ostream&os, Message&m);
    friend class Friendship;

};


#endif //PROJECT_MESSAGE_H
