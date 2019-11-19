#ifndef THING_H
#define THING_H

#include <string>
#include "parentclass.h"
#include "QJsonObject"


class Thing : public ParentClass
{
protected:
    QString name_;
    double volume_;
public:
    Thing();
    Thing(QString name, double price, double volume);
    Thing(const Thing &thing);
    void setVolume(double volume);
    double getVolume() override;
    void setName(QString name);
    QString getName();
    bool operator==(Thing *thing);
    QJsonObject getInfo();
    bool how() override;
    ~Thing() override;
};

#endif // THING_H
