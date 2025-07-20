
#include "Stock.hpp"
#include <string>
#include <stdio.h>
#include <stdbool.h>

Stock::Stock(string name):
    name(name)
{

}

void Stock::addPosition(int volume, double buyPrice){
    positions.push_back(position(volume, buyPrice));
}

double Stock::removePosition(int volume, double sellPrice){
    int mostRecentBuyVolume = positions.back().volume;
    bool mostRecentBuyVolumeLessThanSellVolume = mostRecentBuyVolume < volume;
    double profitLoss;

    if(mostRecentBuyVolumeLessThanSellVolume){
        positions.back().volume -= volume;
        profitLoss = (volume * sellPrice) - (volume * positions.back().buyPrice);

        return profitLoss;
    }

    profitLoss = (volume * sellPrice) - (volume * positions.back().buyPrice);
    int leftOverSellVolume = volume - positions.back().volume;
    positions.pop_back();
    
    return profitLoss + removePosition(leftOverSellVolume, sellPrice);
}