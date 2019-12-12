#include "coinpile.h"
#include "iostream"
#include <math.h>


using namespace std;

CoinPile::CoinPile() = default;

CoinPile::CoinPile(double price):ParentClass(price){}

CoinPile::CoinPile(const CoinPile &coinPile):ParentClass(coinPile.price_){}

double CoinPile::getVolume() const {
    int hundreds = int(this->price_)/100;
    int fifties = int(this->price_ - hundreds * 100)/ 50;
    int tens = int(this->price_ - hundreds * 100 - fifties * 50) / 10;
    int fives = int(this->price_ - hundreds * 100 - fifties
                    * 50 - tens * 10) / 5;
    int ones = int(ceil(this->price_ - hundreds * 100 - fifties
                        * 50 - tens * 10 - fives * 5));
    return hundreds + fifties + tens + fives + ones;
}

bool CoinPile::how(){
    return false;
}

CoinPile::~CoinPile(){}
