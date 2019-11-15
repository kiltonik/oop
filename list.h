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
        Node(): next(nullptr), prev(nullptr), info() {}
        ParentClass* info;
        Node *next= nullptr, *prev= nullptr;
    };
private:
    QJsonObject merge(QJsonObject* obj1, QJsonObject* obj2);
public:
    friend class Iterator;
    Node *head, *tail;
    Iterator begin();
    Iterator end();
    List();
    List(const List &list);
    void deleteElement(ParentClass* info);
    void readListFromFile(const QString& fileName);
    void writeToFile(const QString& fileName);
    void deleteList();
    void add(ParentClass* info);
    int len();
    bool operator==(List list);
    ~List();
};

#endif // LIST_H
