#ifndef NODE_H
#define NODE_H
#include <stddef.h>
template<class T>
struct node
{
    node<T>* next;
    node<T>* prev;
    T data;
};
#endif /* NODE_H */