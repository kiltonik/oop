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


Iterator List::begin() const{
    return Iterator(this->head);
}

Iterator List::end() const{
    return Iterator(nullptr);
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
    for(; itr != list.end(); ++itr){
        this->add(*(*itr));
    }
}

void List::deleteElement(ParentClass &info){
    Node *cur = this->head;
    while(cur){
        if(cur->info->getInfo() == info.getInfo()){
            if(cur == this->head){
                if (this->head == this->tail){
                    delete cur->info;
                    delete cur;
                    this->head = nullptr;
                    this->tail = nullptr;
                    return;
                }
                else{
                    cur->next->prev = nullptr;
                    head = cur->next;
                    delete cur->info;
                    delete cur;
                    return;
                }
            }
            else{
                if (cur == this->tail){
                    tail = cur->prev;
                    tail->next = nullptr;
                    delete cur->info;
                    delete cur;
                    return;
                }
                else{
                    cur->prev->next = cur->next;
                    cur->next->prev = cur->prev;
                    delete cur->info;
                    delete cur;
                    return;
                }
            }
        }
        cur = cur->next;
    }
}

void List::readListFromFile(const QString& fileName){
    this->clearList();
    QFile file(fileName + ".json");
    if (!file.open(QIODevice::ReadOnly)) return;
    QJsonObject temp = QJsonDocument::fromJson(file.readAll()).object();
    for(const auto& i: temp.keys()){
        QJsonObject object = temp.value(i).toObject();
        if(object.value("class").toBool()){
            Thing *thing = new Thing(object.value("name").toString(),
                                     object.value("price").toDouble(),
                                     object.value("volume").toDouble());
            this->add(*thing);
        }
        else{
            CoinPile *coinPile = new CoinPile(object.value("price").toDouble());
            this->add(*coinPile);
        }
    }
    file.close();
}

void List::writeToFile(const QString& fileName) const{
    QFile file(fileName + ".json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return;
    QJsonDocument data;
    int i = 0;
    QJsonObject t;
    for(Iterator itr = Iterator(this->head); itr != this->end(); ++itr){
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

void List::clearList(){
    Node *cur = head;
    while(cur){
        Node *next = cur->next;
        delete cur;
        cur = next;
    }
    head = nullptr;
    tail = nullptr;
}

void List::add(ParentClass &info){
    ParentClass *temp;
    if(info.how()){
        temp = new Thing(*dynamic_cast<Thing*>(&info));
        if (temp->getPrice() <= 0) return;
    }
    else{
        temp = new CoinPile(*dynamic_cast<CoinPile*>(&info));
        if(temp->getPrice() <= 0) return;
    }
    if (info.getPrice() <= 0){
        return;
    }
    Node *tmp = new Node;
    tmp->info = &info;
    if(!head){
        tmp->prev = nullptr;
        head = tail = tmp;
    }
    else{
        Node *cur;
        cur = head;
        while (cur != tail && cur->info->getUnitCost() >= info.getUnitCost())
            cur = cur->next;
        if(cur->info->getUnitCost() < info.getUnitCost()) cur = cur->prev;
        if (cur == tail){
            Node *node;
            node = tail;
            tail = tmp;
            node->next = tail;
            tail->prev = node;
        }

        else{
            if(cur == head){
                tmp->prev = cur;
                tmp->next = cur->next;
                cur->next->prev = tmp;
                cur->next = tmp;
            }
            else{
                if (cur == nullptr){
                    Node *node;
                    node = head;
                    tmp->next = head;
                    node->prev = tmp;
                    head = tmp;
                }
                else{
                    tmp->prev = cur;
                    tmp->next = cur->next;
                    cur->next = tmp;
                    tmp->next->prev = tmp;
                }
            }
        }
    }
}

int List::len() const{
    int len = 0;
    Node *temp;
    temp = head;
    while(temp){
        ++len;
        temp = temp->next;
    }
    return len;
}

bool List::operator==(List &list) const{
    bool flag = true;
    for(Iterator itr = this->begin(), itr2 = list.begin();
        itr != list.end() && itr2 != list.end(); ++itr, ++itr2){
        if(!((*itr)->getInfo() == (*itr2)->getInfo())) flag = false;
    }
    return flag;
}

List::~List(){
    this->clearList();
    delete head;
    delete tail;
}
