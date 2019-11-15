#include "parentclass.h"

ParentClass::ParentClass(){
    price_ = 0;
}

ParentClass::ParentClass(double price){
    price_ = price;
}

void ParentClass::setPrice(double price){
    price_ = price;
}

double ParentClass::getPrice(){
    return price_;
}

QJsonObject ParentClass::getInfo(){
    return QJsonObject({
                           qMakePair(QString("class"), this->how()),
                           qMakePair(QString("price"), QJsonValue(price_))
                       });
}

ParentClass::~ParentClass(){}
