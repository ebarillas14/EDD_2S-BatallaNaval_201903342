#include "../header/queue.h"
#include <iostream>
using namespace std;
template <class T>
queue<T>::queue()
{
    first = NULL;
    last = NULL;
    length = 0;
};

template <class T>
void queue<T>::enqueue(T _data)
{
    node<T> *temp = new node<T>();
    temp->data = _data;
    if (first == NULL)
    {
        first = temp;
        last = temp;
    }
    else
    {
        last->next = temp;
    }
    last = temp;
    length++;
}

template <class T>
T queue<T>::dequeue()
{
    node<T> *temp = new node<T>();
    temp = first;
    first = temp->next;
    length--;
    return temp->data;
}

template <class T>
T queue<T>::peek()
{
    return first->data;
}
