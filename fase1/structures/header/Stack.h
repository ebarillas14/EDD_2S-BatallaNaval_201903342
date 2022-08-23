#ifndef STACK_H
#define STACK_H
#include "node.h"
template <class T>
class Stack
{
public:
    node<T> *first;
    node<T> *last;
    Stack<T>();
    //void insertFirst(T data);
    void push(T data);
    T pop();
    T peek();
    int length;
private:
};
#endif /* STACK_H */