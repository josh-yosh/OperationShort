
#include "Stock.hpp"
#include <string>
#include <stdio.h>
#include <stdbool.h>
#include <iostream>

Stock::Stock(string name): // fix name to be ticker symbold
    name(name), totalVolume(0), priceBasis(0.0), totalProfitLoss(0.0), positions(){}

void Stock::addPosition(int volume, double buyPrice){
    priceBasis += volume * buyPrice; //finds the money used to buy the stock
    totalVolume += volume; //alters the total volume
    positions.push_back(position(volume, buyPrice)); //adds the position
}

double Stock::sellPosition(int volume, double sellPrice){ // volume cannot be larger than how much we have
    int mostRecentBuyVolume = positions.back().volume;
    bool mostRecentBuyVolumeLessThanOrEqualSellVolume = mostRecentBuyVolume <= volume;

    double cashFromSell = volume * sellPrice; // total amount of money the stock is worth
    double costBasisOfSoldShares;
    
    //we go from the top of the stack and pop until we run out of volume needed to sell, or in other words
    //until our order is fufilled
    while(mostRecentBuyVolumeLessThanOrEqualSellVolume){
        //selling most recent position
        volume -= mostRecentBuyVolume;
        totalVolume -= mostRecentBuyVolume;
        costBasisOfSoldShares += mostRecentBuyVolume * positions.back().buyPrice; 
        positions.pop_back();
        
        //if we end at 0, we end. if not zero, continue loop
        bool positionSizeNotZero = !(positions.size() == 0);
        if(positionSizeNotZero){
            mostRecentBuyVolume = positions.back().volume;
            mostRecentBuyVolumeLessThanOrEqualSellVolume = mostRecentBuyVolume <= volume;
        } else {
            mostRecentBuyVolumeLessThanOrEqualSellVolume = false;
        }
    }

    positions.back().volume -= volume;
    totalVolume -= volume;
    costBasisOfSoldShares += volume * positions.back().buyPrice;

    double profitLoss = cashFromSell - costBasisOfSoldShares;
    return profitLoss;
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