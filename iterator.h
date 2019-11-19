#ifndef ITERATOR_H
#define ITERATOR_H
#include "list.h"

class Iterator
{
private:
    List::Node *nodeptr;
public:
    friend class List;

    Iterator(List::Node* ptr);
    const Iterator operator++();
    const Iterator operator--();
    ParentClass* &operator *();
    bool operator==(const Iterator& ptr);
    bool operator!=(const Iterator& ptr);
    Iterator();
};

#endif // ITERATOR_H
