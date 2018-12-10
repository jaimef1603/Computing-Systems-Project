#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <vector>

using namespace std;

template <typename A>
class ArrayList: public vector <A>
{
public:
    ArrayList();
    ArrayList(const A &a);
    ArrayList(const A &&a);
    ArrayList(size_t _n, const A& = A() );
    ArrayList(const vector<A> &);
    ArrayList(const vector<A> &&);
    ArrayList(const ArrayList<A> &);
    ArrayList(const ArrayList<A> &&);

    void pushFront(const A&);
    void pushFront(const A&&);
    void pushBack(const A&);
    void pushBack(const A&&);
    bool remove(const A&);
    bool removeByIndex(unsigned index);
    //A& operator[] (unsigned index);
    ArrayList<A>& operator = ( const ArrayList<A>& );
    ArrayList<A>& operator = ( const ArrayList<A>&& );
    ArrayList<A>& operator = ( const vector<A>& );
    ArrayList<A>& operator = ( const vector<A>&& );
    vector<A>& to_vector();





};


#include "ArrayList.tpp"

#endif // ARRAYLIST_H
