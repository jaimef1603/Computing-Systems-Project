
template <typename T> Node<T>::Node(const T &d): data(d){}

template <typename T> Node<T>::Node(const T &d, Node &n): data(d),next(&n){}

template <typename T> Node<T>::Node(const T &d, Node &n, Node &p): data(d),next(&n),previous(&p){}


template <typename T> Node<T>::Node(const Node<T> &nN): data(nN.data),next(nN.next),previous(nN.previous){}


template <typename T> Node<T>::~Node(){
    next=nullptr;
    previous=nullptr;
}


template <typename T> T Node<T>::getdata(){
    return data;
}

template <typename T> void Node<T>::setdata(int d){
    data=d;
}

template <typename T> Node<T>* Node<T>::getnext(){
    return next;
}

template <typename T> void Node<T>::setnext(Node *n){
    next=n;
}

template <typename T> Node<T>* Node<T>::getprevious(){
    return previous;
}
template <typename T> void Node<T>::setprevious(Node *n){
    previous=n;
}
template <typename T> void Node<T>::remove(){
    if (previous!=nullptr){
        previous->setnext(next);
    }
    if (next!=nullptr){
        next->setprevious(previous);
    }
    this->~Node();
}

template <class T> Node<T>& Node<T>::operator=(const Node<T> &nN){
    data=nN.data;
    next=nN.next;
    return *this;
}
