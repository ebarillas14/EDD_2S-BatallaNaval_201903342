#include "../header/linkedList.h"
using namespace std;
template <class T>
linkedList<T>::linkedList()
{
    first = NULL;
    last = NULL;
    length = 0;
};

template <class T>
void linkedList<T>::insertFirst(T _data)
{
    node<T> *temp = new node<T>();
    temp->data = _data;
    temp->next = first;
    first = temp;
    length++;
};

template <class T>
T linkedList<T>::get(int _pos)
{
    node<T> *temp = new node<T>();
    temp = first;
    int pos = 0;
    while (pos != _pos)
    {
        temp = temp->next;
        pos++;
    }
    return temp->data;
};


template <class T>
void linkedList<T>::update(T _data, int _pos)
{
    node<T> *temp = new node<T>();
    temp = first;
    int pos = 0;
    while (pos != _pos)
    {
        temp = temp->next;
        pos++;
    }
    temp->data  = _data;
};