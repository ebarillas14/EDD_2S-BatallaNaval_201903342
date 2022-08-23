#include "node.h"
template <class T>
class linkedList
{
public:
    node<T> *first;
    node<T> *last;
    int length;
    linkedList<T>();
    void insertFirst(T data);
    void update(T _data, int pos);
    T get(int pos);
private:
};