#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "Node.h"
#include <iostream>

using namespace std;

template <typename A> class ArrayList
{

private:
    int size;
    Node<A> *head;
    Node<A> *tail;
public:
    ArrayList();
    ~ArrayList();
    int getsize();
    int length();
    Node<A>& pushFront(const A&);
    Node<A>& pushBack(const A&);
    int remove(const A&);
    void removebyindex(int index);
    A operator[] (int index)const;
    ArrayList<A>& operator=(const ArrayList<A>& );

};

#include "ArrayList.tpp"

#endif // ARRAYLIST_H
