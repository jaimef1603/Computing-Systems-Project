#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "Node.h"
#include <iostream>

using namespace std;

template <typename A> class ArrayList
{

private:
    unsigned size;
    Node<A> *head;
    Node<A> *tail;
public:
    ArrayList();
    ~ArrayList();
    unsigned getsize();
    int length();
    Node<A>& pushFront(const A&);
    Node<A>& pushBack(const A&);
    bool remove(const A&);
    void removebyindex(unsigned index);
    A operator[] (unsigned index)const;
    ArrayList<A>& operator=(const ArrayList<A>& );

};

#include "ArrayList.tpp"

#endif // ARRAYLIST_H
