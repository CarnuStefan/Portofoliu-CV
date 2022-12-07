//
// Created by crnst on 5/5/2022.
//

#ifndef PROJECT_LISTA_H
#define PROJECT_LISTA_H

#include <vector>
#include <algorithm>

template<class T>
class Lista {
protected:
    std::vector<T> lst;
public:
    Lista() = default;

    void add(T elem) {
        this->lst.push_back(elem);

    }

    void remove(T e) {
        for (int i = 0; i < lst.size(); ++i) {
            if (lst[i]==e)
            {
                if (i==lst.size()-1)
                {
                    lst.pop_back();
                }
                for (int j = i+1; j <lst.size() ; ++j) {
                    lst[i]=lst[j];
                }
            }
        }
    }

    void update(T e)
    {
        for (int i = 0; i < lst.size(); ++i) {
            if (lst[i]==e)
            {
                lst[i]=e;
            }
        }
    }

    int size() const {
        return lst.size();
    }

    std::vector<T> getAll() {
        return this->lst;
    }

    int getpos(T e)
    {
        for (int i = 0; i < lst.size(); ++i) {
            if (lst[i]==e)
                return i;
        }
        return -1;
    }

    Lista<T> &operator=(Lista<T> *lst2) {
        if (this != lst2)
            this->lst = lst2->lst;
        return *this;
    }

    bool operator==(Lista<T> lst2) {
        int ok=0;
        if (this->lst.size()==lst2.lst.size())
        {
            ok=1;
            for (int i = 0; i < lst.size(); ++i) {
                if (lst[i]!=lst2.lst[i])
                    ok=0;
            }
        }
        if (ok) return true;
        return false;
    }

    bool operator!=(Lista<T> lst2) {
        int ok=0;
        if (this->lst.size()==lst2.lst.size())
        {
            ok=1;
            for (int i = 0; i < lst.size(); ++i) {
                if (lst[i]!=lst2.lst[i])
                    ok=0;
            }
        }
        if (ok) return false;
        return true;
    }

    T operator[](int index) {
        return this->lst[index];
    }

    ~Lista()=default;
};
#endif //PROJECT_LISTA_H
