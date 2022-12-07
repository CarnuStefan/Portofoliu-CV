//
// Created by crnst on 5/10/2022.
//

#ifndef PROJECT_FRIENDSHIP_H
#define PROJECT_FRIENDSHIP_H


#include "Message.h"
#include "../TAD/Lista.h"

class Friendship {
private:
    int idprincipal{};
    int idprieten{};
    Lista<Message> conversatie;
public:
    Friendship();
    Friendship(int idpr,int idp, const Lista<Message>& conv);
    Friendship(Friendship const&f);
    int getIDPrin() const;
    int getIDFriend() const;
    Lista<Message> getConvo();
    void setIDPrin(int idpr);
    void setIDFriend(int idp);
    void setConvo(const Lista<Message>& conv);
    void addMessage(const Message &m );
    void deleteMessage(int i);
    Friendship& operator=(const Friendship &f) noexcept;
    bool operator==(Friendship const& f) const;
    bool operator!=(Friendship const& f) const;
    bool operator>(Friendship const& f);
    bool operator<(Friendship const& f);
    ~Friendship();


};


#endif //PROJECT_FRIENDSHIP_H
