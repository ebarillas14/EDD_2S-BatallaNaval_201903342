#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
template <class T>
class queue
{
public:
    node<T> *first;
    node<T> *last;
    queue<T>();
    //void insertFirst(T data);
    void enqueue(T data);
    T dequeue();
    T peek();
    int length;
private:
};
#endif /* QUEUE_H */