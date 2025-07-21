
#include "Stock.hpp"
#include <string>
#include <stdio.h>
#include <stdbool.h>
#include <iostream>

Stock::Stock(string name):
    name(name)
{

}

void Stock::addPosition(int volume, double buyPrice){
    priceBasis += volume * buyPrice;
    totalVolume += volume;
    positions.push_back(position(volume, buyPrice));
}

double Stock::sellPosition(int volume, double sellPrice){ // FIX THIS RECURSION, SOMETHING IS WRONG HERE 
    int mostRecentBuyVolume = positions.back().volume;
    bool mostRecentBuyVolumeLessThanSellVolume = mostRecentBuyVolume < volume;
    double profitLoss;
    double cashFromSell;

    if(mostRecentBuyVolumeLessThanSellVolume){
        positions.back().volume -= volume;
        profitLoss = (volume * sellPrice) - (volume * positions.back().buyPrice);
        cashFromSell +=
        totalProfitLoss = profitLoss;
        return profitLoss;
    }

    profitLoss = (volume * sellPrice) - (volume * positions.back().buyPrice);
    int leftOverSellVolume = volume - positions.back().volume;
    positions.pop_back();
    
    return profitLoss + sellPosition(leftOverSellVolume, sellPrice);
}

double Stock::getTotalStockPrice(double currentPrice){
    int totalStockPrice = currentPrice * totalVolume;
    return totalStockPrice;
}

int Stock::getTotalVolume(){
    return totalVolume;
}

string Stock::getName(){
    return name;
}

double Stock::sellAll(double currentStockPrice){
    return sellPosition(getTotalVolume(), currentStockPrice);
}

void Stock::printPositions(){
    if(positions.size() == 0){
        cout << "You have no holdings for " << name << "\n"; 
    } else {
        cout << "Symbol: " << name << "\n";
        for(int i = 0; i < positions.size(); i++){
            cout << "[Volume: " << positions[i].volume << ", Price: " << positions[i].buyPrice << "\n";
        }
        cout << "\n";   
    }
}