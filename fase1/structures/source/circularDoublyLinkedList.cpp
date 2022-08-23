#include "../header/circularDoublyLinkedList.h"
#include <iostream>
using namespace std;
template <class T>
circularDoublyLinkedList<T>::circularDoublyLinkedList()
{
    first = NULL;
    last = NULL;
    count = 0;
};

// template <class T>
// void circularDoublyLinkedList<T>::insertFirst(T _data)
// {

// };

template <class T>
void circularDoublyLinkedList<T>::insertLast(T _data)
{
    node<T> *temp = new node<T>();
    temp->data = _data;
    if (first == NULL)
    {
        count = 1;
        first = temp;
        last = temp;
        temp->next = first;
        temp->prev = last;
    }
    else
    {
        last->next = temp;
        temp->prev = last;
        temp->next = first;
        last = temp;
        first->prev = last;
        count++;
    }
}

template <class T>
void circularDoublyLinkedList<T>::modify(T _data, int _pos)
{
    node<T> *temp = first;
    int pos = 0;
    while (temp != NULL)
    {
        if (_pos == pos)
        {
            temp->data = _data;
        }
        else
        {
            temp = temp->next;
            pos++;
        }
    }
}

template <class T>
void circularDoublyLinkedList<T>::remove(int _pos)
{
    node<T> *actual = first;
    node<T> *previous = last;
    int pos = 0;
    do
    {
        if (pos == _pos)
        {
            if (actual == first)
            {
                first = first -> next;
                last-> next = first;
                last->prev = last;
            }
            else if (actual == last)
            {
                last = previous;
                first->prev = last;
                last->next = first;
            }
            else
            {
                previous->next = actual->next;
                actual->next->prev = previous;
            }
        }
        previous = actual;
        actual = actual->next;
        pos ++;
    } while (pos != _pos);
}

template <class T>
T circularDoublyLinkedList<T>::get(int _pos){
    node<T> *temp = new node<T>();
    temp = first;
    int pos = 0;
    while (pos != _pos)
    {
        pos++;
        temp = temp->next;
    }
    return temp->data;
}