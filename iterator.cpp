#include "iterator.h"

Iterator::Iterator(List::Node* ptr){
    this->nodeptr = ptr;
}

const Iterator Iterator::operator++(int i){
    nodeptr = nodeptr->next;
    return *this;
}

const Iterator Iterator::operator--(int i){
    nodeptr = nodeptr->prev;
    return *this;
}

ParentClass* &Iterator::operator*(){
    return nodeptr->info;
}

bool Iterator::operator==(const Iterator& ptr){
    return nodeptr==ptr.nodeptr;
}

bool Iterator::operator!=(const Iterator& ptr){
    return nodeptr!=ptr.nodeptr;
}
