#include "thing.h"
#include "iostream"
#include <string>
#include <utility>
#include "QJsonObject"




Thing::Thing() = default;
Thing::Thing(QString name, double price, double volume){
    name_ = name;
    price_ = price;
    volume_ = volume;
}

Thing::Thing(const Thing &thing):ParentClass(){
    name_ = thing.name_;
    price_ = thing.price_;
    volume_ = thing.volume_;
}

void Thing::setName(QString name){
    name_= name;
}

QString Thing::getName(){
    return name_;
}

void Thing::setVolume(double volume){
    this->volume_ = volume;
}

double Thing::getVolume(){
    return this->volume_;
}

bool Thing::operator==(Thing *thing){
    return this->getInfo() == thing->getInfo();
//    return (this->name_ == thing->getName() && (this->price_ == thing->getPrice())  &&
//            (this->volume_ - thing->getVolume()) );
}

QJsonObject Thing::getInfo(){
    return QJsonObject({
                           qMakePair(QString("class"), this->how()),
                           qMakePair(QString("name"), name_),
                           qMakePair(QString("price"), QJsonValue(price_)),
                           qMakePair(QString("volume"), QJsonValue(volume_))
                       });
}

bool Thing::how(){
    return true;
}

Thing::~Thing(){}
