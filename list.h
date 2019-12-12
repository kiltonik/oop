#ifndef LIST_H
#define LIST_H

#include <cassert>
#include "coinpile.h"
#include "thing.h"
#include <fstream>
#include <iostream>
#include <io.h>
#include "QJsonObject"

class Iterator;

class List
{
    struct Node{
        ParentClass* info;
        Node *next= nullptr, *prev= nullptr;
    };
private:
    Node *head, *tail;
public:
    friend class Iterator;
    Iterator begin() const;
    Iterator end() const;
    List();
    List(const List &list);
    void deleteElement(ParentClass& info);
    void readListFromFile(const QString& fileName);
    void writeToFile(const QString& fileName) const;
    void clearList();
    void add(ParentClass& info);
    int len() const;
    bool operator==(List &list) const;
    ~List();
};

#endif // LIST_H
