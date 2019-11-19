#include "list.h"
#include <cassert>
#include "thing.h"
#include <fstream>
#include <iostream>
#include <io.h>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include "iterator.h"


Iterator List::begin(){
    Iterator *begin = new Iterator(this->head);
    return *begin;
}

Iterator List::end(){
    Iterator end(nullptr);
    return end;
}
List::List()
{
    this->head = nullptr;
    this->tail = nullptr;
}

List::List(const List &list){
    Iterator itr = Iterator(list.head);
    this->head = nullptr;
    this->tail = nullptr;
    for(; itr != List::end(); itr++){
        this->add(*itr);
    }
}

void List::deleteElement(ParentClass *info){
    Node *cur = this->head;
    while(cur){
        if(cur->info->getInfo() == info->getInfo()){
            if(cur == this->head){
                if (this->head == this->tail){
                    delete cur;
                    this->head = nullptr;
                    this->tail = nullptr;
                    return;
                }
                else{
                    cur->next->prev = nullptr;
                    head = cur->next;
                    delete cur;
                    return;
                }
            }
            else{
                if (cur == this->tail){
                    tail = cur->prev;
                    tail->next = nullptr;
                    delete cur;
                    return;
                }
                else{
                    cur->prev->next = cur->next;
                    cur->next->prev = cur->prev;
                    delete cur;
                    return;
                }
            }
        }
        cur = cur->next;
    }
}

void List::readListFromFile(const QString& fileName){
    this->deleteList();
    QFile file(fileName+".json");
    if (!file.open(QIODevice::ReadOnly)) return;
    QJsonObject temp = QJsonDocument::fromJson(file.readAll()).object();
    for(const auto& i: temp.keys()){
        QJsonObject object = temp.value(i).toObject();
        if(object.value("class").toBool()){
            Thing *thing = new Thing(object.value("name").toString(), object.value("price").toDouble(), object.value("volume").toDouble());
            this->add(thing);
        }
        else{
            CoinPile *coinPile = new CoinPile(object.value("price").toDouble());
            this->add(coinPile);
        }
    }
    file.close();
}

void List::writeToFile(const QString& fileName){
    QFile file(fileName+".json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) return;
    QJsonDocument data;
    int i = 0;
    QJsonObject t;
    for(Iterator itr = Iterator(this->head); itr != this->end(); itr++){
        if((*itr)->how()){
            Thing *temp = dynamic_cast<Thing*>(*itr);
            t.insert(QString::number(i), temp->getInfo());
        }
        else{
            CoinPile *temp = dynamic_cast<CoinPile*>(*itr);
            t.insert(QString::number(i), temp->getInfo());
        }
        ++i;
    }
    file.write(QJsonDocument(t).toJson(QJsonDocument::Indented));
    file.close();
}

void List::deleteList(){
    Node *cur = head;
    for (Iterator *itr = new Iterator(head); itr != nullptr; ++itr){
        delete itr;
    }
//    while(cur){
//        if (head == tail){

//            delete cur;
//        }
//        else{
//            delete cur->prev;
//            cur = cur->next;

//        }
//    }
}

void List::add(ParentClass* info){
    Thing *tmp = dynamic_cast<Thing*>(info);
    if (info->getPrice() <= 0){
        return;
    }
    if (tmp){
        if(tmp->getVolume() <= 0) return;
    }

    Node *temp = new Node;
    temp->info = info;
    if(!head){
        temp->prev = nullptr;
        head = tail = temp;
    }
    else{
        Node *cur;
        cur = head;
        while (cur != tail && cur->info->getUnitCost() >= info->getUnitCost()) cur = cur->next;
        if(cur->info->getUnitCost() < info->getUnitCost()) cur = cur->prev;
        if (cur == tail){
            Node *node;
            node = tail;
            tail = temp;
            node->next = tail;
            tail->prev = node;
        }

        else{
            if(cur == head){
                temp->prev = cur;
                temp->next = cur->next;
                cur->next = temp;
            }
            else{
                if (cur == nullptr){
                    Node *node;
                    node = head;
                    temp->next = head;
                    node->prev = temp;
                    head = temp;
                }
                else{
                    temp->prev = cur;
                    temp->next = cur->next;
                    cur->next = temp;
                    temp->next->prev = temp;
                }
            }
        }
    }
}

int List::len(){
    int len = 0;
    Node *temp;
    temp = head;
    while(temp){
        ++len;
        temp = temp->next;
    }
    return len;
}

bool List::operator==(List list){
    bool flag = true;
    for(Iterator itr = this->begin(), itr2 = list.begin();itr != List::end() && itr2 != List::end();itr++, itr2++){
        if(!(*itr == *itr2)) flag = false;
    }
    return flag;
}

List::~List(){
    std::cout << "List destructed" << std::endl;
    this->deleteList();
}
