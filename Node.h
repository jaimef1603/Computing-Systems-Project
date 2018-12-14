#ifndef NODE_H
#define NODE_H

template <typename T> class Node{
  private:
  T data;
  Node<T> *next;
  Node<T> *previous;

  public:
  Node(const T &d);
  Node(const T &d, Node<T> &n);
  Node(const T &d, Node<T> &n, Node<T> &p);
  Node(const Node<T> &nN);
  ~Node<T>();
  T getdata();
  void setdata(int d);
  Node<T>* getnext();
  void setnext(Node<T> *n);
  Node<T>* getprevious();
  void setprevious(Node<T> *n);
  void remove();
  Node<T>& operator=(const Node<T> &nN);

};

#include "Node.tpp"

#endif
