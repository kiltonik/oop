#ifndef COINPILE_H
#define COINPILE_H

#include "thing.h"


class CoinPile: public ParentClass
{
public:
    CoinPile();
    CoinPile(double price);
    CoinPile(const CoinPile &coinPile);
    double getVolume() override;
    bool how() override;
    ~CoinPile() override;
};

#endif // COINPILE_H
