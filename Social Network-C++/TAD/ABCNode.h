#ifndef PROJECT_ABCNODE_H
#define PROJECT_ABCNODE_H
#include<iostream>
using namespace std;
template<typename T>
class ABC;

template<class T>
class ABCNode{
private:
    T info;
    ABCNode<T>* left;
    ABCNode<T>* right;
public:
    ABCNode(T info, ABCNode<T> *left, ABCNode<T> *right) : info(info), left(left), right(right) {}

    ABCNode<T> &operator=(ABCNode<T> *node) {
        if (this != node)
            this->info = node->info;
        return *this;
    }

    bool operator!=(ABCNode<T> *node)
    {
        return (this->info!=node->info);
    }

    friend class ABC<T>;
};

#endif //PROJECT_ABCNODE_H
