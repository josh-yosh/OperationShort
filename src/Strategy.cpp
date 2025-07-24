#include "Strategy.hpp"
#include "UsingImGui.h"
#include "OrderTypeEnum.hpp"

Strategy::Strategy(double startingCash):
    startingCash(startingCash), portfolio(startingCash), availableToBuy(true), dayInfo(), previousCloseMinuteClose(0.0){}

void Strategy::buy(string stockSymbol, int volume, double currentPrice){
    portfolio.buyStock(stockSymbol, volume, currentPrice);
    
}   

void Strategy::sell(string stockSymbol, int volume, double currentPrice){
    portfolio.sellStock(stockSymbol, volume, currentPrice);

}

int Strategy::getOrderVolume(){
    return orderVolume;
}
double Strategy::getStartingCash(){
    return startingCash;
}
void Strategy::setOrderVolume(int orderVolume){
    this->orderVolume = orderVolume;
}
Portfolio Strategy::getPortfolio(){
    return portfolio;
}

OrderType Strategy::waveRiding(string stockSymbol, double currentPrice, vector<minuteTickerInfo> dayInfo){
    
    if(dayInfo.size() == 1){
        peakOrDipPrice = dayInfo[0].close;
        this->dayInfo = dayInfo;
    }
    if(dayInfo.size() > 2){
        this->dayInfo = dayInfo;
        double mostRecentClosePrice = dayInfo.back().close;
        int totalPossibleBuyAmount = int (portfolio.getCashOnHand() / currentPrice);
        if(mostRecentClosePrice > peakOrDipPrice && availableToBuy){ //if the previous price is lower than the current price, buy
            orderVolume = totalPossibleBuyAmount;
            buy(stockSymbol, totalPossibleBuyAmount, currentPrice);
            availableToBuy = false;
            return OrderType::MARKETBUY; 
        } else if (mostRecentClosePrice < peakOrDipPrice && !availableToBuy){ //if the previous price is less than the current price, sell
            orderVolume = portfolio.getStockCount(stockSymbol);
            sell(stockSymbol, portfolio.getStockCount(stockSymbol), currentPrice);
            availableToBuy = true;
            peakOrDipPrice = mostRecentClosePrice;
            return OrderType::MARKETSELL;
        } else {
            peakOrDipPrice = mostRecentClosePrice;
        }
    }
    
    return OrderType::NO_ORDER;
}
