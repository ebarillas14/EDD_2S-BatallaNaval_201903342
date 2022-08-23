#ifndef CIRCULARDOUBLYLINKEDLIST_H
#define CIRCULARDOUBLYLINKEDLIST_H
#include "node.h"
template <class T>
class circularDoublyLinkedList
{
public:
    node<T> *first;
    node<T> *last;
    circularDoublyLinkedList<T>();
    //void insertFirst(T data);
    void insertLast(T data);
    void modify(T data, int pos);
    void remove(int pos);
    T get(int pos);
    int count;
private:
};
#endif /* NODE_H */