#include "ArrayList.h"

template <typename A> ArrayList<A>::ArrayList()
{
    size=0;
    head=nullptr;
    tail=nullptr;
}

template <typename A> ArrayList<A>::~ArrayList(){
    Node <A> *next;
    for (int i=size; i>0; i--){
        if(head!=nullptr){
            next=head->getprevious();
            head->remove();
            head=next;
        }else{
            tail=nullptr;
        }
    }
}

template <typename A> int ArrayList <A> ::getsize(){
    return size;
}
template <typename A> int ArrayList<A>::length(){
    return size-1;
}


template <typename A> Node<A>& ArrayList<A>::pushFront(const A &d){
    Node <A>*n=new Node<A>(d);
    if (head!=nullptr){
        n->setprevious(head);
        head->setnext(n);
    }

    head=n;

    if (tail==nullptr){
        tail=n;
    }
    size++;
    return *n;
}

template <typename A> Node<A>& ArrayList<A>::pushBack(const A &d){
    Node <A>*n=new Node<A>(d);
    if (tail!=nullptr){
        n->setnext(tail);
        tail->setprevious(n);
    }
    tail=n;

    if (head==nullptr){
        head=n;
    }
    size++;
    return *n;
}


template <typename A> int ArrayList<A>::remove(const A &d){
    Node <A>*target=tail;
    for (int i=0; i<size; i++){
        if(target->getdata()==d){
            if (i==0){tail=target->getnext();}
            if (i==size-1){head=target->getnext();}
            target->remove();
            size--;
            return 1;
        } else{
            target = target->getnext();
        }
    }
    return 0;
}



template <typename A> void ArrayList<A>::removebyindex(int index){
    Node<A> *target=tail;
    for (int i=0; i<index; i++){
        target=target->getnext();
    }
    target->remove();
}



template <typename A> A ArrayList<A>::operator[](int index)const{
    Node <A>*target=tail;
    for (int i=0; i<index; i++){
        target=target->getnext();
    }
    return target->getdata();
}


template <typename A> ArrayList<A>& ArrayList<A>::operator=(const ArrayList<A>& list){
    Node <A> *next;

        if ((head!=nullptr || tail!=nullptr) && size>0){
        for (int i=size; i>0; i--){
            if(head!=nullptr){
                next=head->getprevious();
                head->remove();
                head=next;
            }else{
                tail=nullptr;
            }

        }
    }
        head=nullptr;
        tail=nullptr;
        for(int i=0; i<list.size; i++){
            this->pushFront(list[i]);
        }
        return *this;
}

    //void ArrayList::remove(const int d){}
