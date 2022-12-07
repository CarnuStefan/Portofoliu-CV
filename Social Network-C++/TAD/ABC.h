#ifndef PROJECT_ABC_H
#define PROJECT_ABC_H

#include <vector>
#include "ABCNode.h"
#include <iostream>

template<class T>
class ABC {
private:
    ABCNode<T> *root;

    void add(ABCNode<T> *ad, T elem) {

        if (ad->info > elem) { // adaugam pe stanga
            if (ad->left != nullptr) {
                add(ad->left, elem);
            } else {
                ad->left = new ABCNode<T>(elem, nullptr, nullptr);
            }
        } else {  //adaugam in dreapta
            if (ad->right != nullptr) {
                add(ad->right, elem);
            } else {
                ad->right = new ABCNode<T>(elem, nullptr, nullptr);
            }
        }
    }

    ABCNode<T> *minnod(ABCNode<T> *node) {
        ABCNode<T> *curent = node;
        while (curent->left != nullptr)
            curent = curent->left;
        return curent;
    }

    ABCNode<T>* del(ABCNode<T>* &r, T inf) {
        if (r == nullptr)
            return r;
        if (inf < r->info)
            r->left = del(r->left, inf);
        else if (inf > r->info)
            r->right = del(r->right, inf);
        else {
            if (r->left == nullptr && r->right == nullptr) {
                delete r;
                r = nullptr;
                return r;
            } else if (r->left == nullptr) {
                ABCNode<T>* t = r->right;
                delete r;
                r = t;
                return r;
            } else if (r->right == nullptr) {
                ABCNode<T>* t = r->left;
                delete r;
                r = t;
                return r;
            }
            ABCNode<T> *t = minnod(r->right);
            r->info = t->info;
            r->right = del(r->right, t->info);
        }
        return r;
    }

    void toVector(ABCNode<T> *ad, vector<T> &vec) {
        if (ad != nullptr) {
            toVector(ad->left, vec);
            vec.push_back(ad->info);
            toVector(ad->right, vec);
        }
    }

public:
    ABC() { this->root = nullptr; }

    void addItem(T elem) {
        if (this->root == nullptr) this->root = new ABCNode<T>(elem, nullptr, nullptr);
        else add(this->root, elem);
    }

    void delItem(T elem) {
        if (this->root != nullptr)
            del(this->root, elem);
    }
    vector<T> getAll() {
        vector<T> all;
        toVector(root, all);
        return all;
    }

    ABC<T> &operator=(ABC<T> *abc) {
        if (this->root != abc->root)
            this->root = abc->root;
        return *this;
    }

};

#endif //PROJECT_ABC_H
