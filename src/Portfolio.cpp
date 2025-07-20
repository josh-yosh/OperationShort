#include "Portfolio.hpp"
#include <vector>
#include <stdbool.h>
#include <cassert>
#include "backtester.hpp"
#include <iostream>

Portfolio::Portfolio(double cashOnHand): 
    cashOnHand(cashOnHand), totalProfitLoss(0.0), totalValue(cashOnHand){}

void Portfolio::sellStock(string stockSymbol, int volume, Backtester backtesterInstance){
    int indexOfStock = findIndexOfStock(stockSymbol);
    int changeInCash = stockPortfolio[indexOfStock].sellPosition(volume, backtesterInstance.getCurrentPrice());
    totalProfitLoss += changeInCash;
    addCash(changeInCash);
}

void Portfolio::sellStockAll(string stockSymbol, Backtester backtesterInstance){
    int indexOfStock = findIndexOfStock(stockSymbol);

    int changeInCash = stockPortfolio[indexOfStock].sellPosition(stockPortfolio[indexOfStock].getTotalVolume(), backtesterInstance.getCurrentPrice());
    totalProfitLoss += changeInCash;
    addCash(changeInCash);
}

int Portfolio::findIndexOfStock(string stockSymbol){
    bool inBounds = true;
    bool foundIndex = false;
    int sizeOfStockPortfolio = stockPortfolio.size();
    assert(sizeOfStockPortfolio > 1);

    int index = 0;
    int returnIndex;

    while(!foundIndex && inBounds){
        if(index == sizeOfStockPortfolio){
            returnIndex = -1;
            inBounds = false;
        } else {
            foundIndex = stockPortfolio[index].getName() == stockSymbol;

            if(foundIndex){
                returnIndex = index;
            }
        }
    }
    return returnIndex;
}

void Portfolio::buyStock(string stockSymbol, int volume, Backtester backtesterInstance){
    int indexOfStock = findIndexOfStock(stockSymbol);
    stockPortfolio[indexOfStock].addPosition(volume, backtesterInstance.getCurrentPrice());
    removeCash(volume * backtesterInstance.getCurrentPrice());
}

double Portfolio::getCashOnHand(){
    return cashOnHand;
}
void Portfolio::removeCash(double amount){
    cashOnHand -= amount;
}
void Portfolio::addCash(double amount){
    cashOnHand += amount;
}
double Portfolio::getTotalValue(Backtester backtesterInstance){

    assert(stockPortfolio.size() > 0);

    double valueOfStocks;

    for(int i = 0; i < stockPortfolio.size(); i++){
        valueOfStocks += backtesterInstance.getCurrentPrice() * stockPortfolio[i].getTotalVolume();
    }

    totalValue = cashOnHand + valueOfStocks;
    return totalValue;
}
vector<Stock> Portfolio::getStockList(){
    return stockPortfolio;
}

void Portfolio::printStockList(){
    if(stockPortfolio.size() == 0 ){
        cout << "You have no holdings in your Portfolio";
    } else {
        for(int i = 0; i < stockPortfolio.size(); i++){
            stockPortfolio[i].printPositions();
        }
    }
}

vector<Stock> stockPortfolio;
double totalValue;
double cashOnHand;
double totalProfitLoss;