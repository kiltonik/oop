#include "thing.h"
#include "iostream"
#include <string>
#include <utility>
#include "QJsonObject"




Thing::Thing(){
    name_ = QString("table");
    price_ = 1;
    volume_ = 1;
}

Thing::Thing(QString name, double price, double volume){
    name_ = name;
    if (price <= 1) price_ = 1;
    else price_ = price;
    if (volume <= 1) volume_ = 1;
    else volume_ = volume;
}

Thing::Thing(const Thing &thing):ParentClass(){
    name_ = thing.name_;
    price_ = thing.price_;
    volume_ = thing.volume_;
}

void Thing::setName(QString name){
    if (name.isEmpty()) name_ = QString("table");
    else name_= name;
}

QString &Thing::getName(){
    return name_;
}

// проверка на вводимые данные, инициализация в конструкторе
void Thing::setVolume(double volume){
    if(volume <= 0) return;
    else this->volume_ = volume;
}

double Thing::getVolume() const {
    return this->volume_;
}

bool Thing::operator==(Thing &thing){
    return this->getInfo() == thing.getInfo();
}

QJsonObject Thing::getInfo(){
    return QJsonObject({
                           qMakePair(QString("class"), how()),
                           qMakePair(QString("name"), name_),
                           qMakePair(QString("price"), QJsonValue(this->getPrice())),
                           qMakePair(QString("volume"), QJsonValue(volume_))
                       });
}

bool Thing::how(){
    return true;
}

Thing::~Thing(){}
