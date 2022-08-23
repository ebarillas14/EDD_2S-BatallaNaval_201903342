#include "../header/Stack.h"
#include <iostream>
using namespace std;
template <class T>
Stack<T>::Stack()
{
    first = NULL;
    last = NULL;
    length = 0;
};

template <class T>
void Stack<T>::push(T _data)
{
    node<T> *temp = new node<T>();
    temp->data = _data;
    temp->next = first;
    first = temp;
    length++;
}

template <class T>
T Stack<T>::pop()
{
    node<T> *temp = new node<T>();
    temp = first;
    if (first != NULL)
    {
        first = first->next;
        length--;
        return temp->data;
    }
    else{
        return NULL;
    }
}

template <class T>
T Stack<T>::peek()
{
    return first->data;
}
