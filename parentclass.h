#ifndef PARENTCLASS_H
#define PARENTCLASS_H

#include <QJsonObject>



class ParentClass
{
protected:
    double price_;
public:
    ParentClass();
    ParentClass(double price);
    void setPrice(double price);
    double getPrice();
    virtual bool how() = 0;
    virtual double getVolume() const = 0;
    double getUnitCost();
    QJsonObject getInfo();
    virtual ~ParentClass();
};

#endif // PARENTCLASS_H
