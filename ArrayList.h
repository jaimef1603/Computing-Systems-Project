#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "Node.h"


template <typename A> class ArrayList
{

private:
    int size;
    Node<A> *head;
    Node<A> *tail;
public:
    ArrayList();
    int getsize();
    int length();
    Node<A>& pushFront(const A&);
    Node<A>& pushBack(const A&);
    int remove(const A&);
    A operator[] (int index);

};

#include "ArrayList.tpp"

#endif // ARRAYLIST_H
