#include "Strategy.hpp"
#include "UsingImGui.h"
#include "OrderTypeEnum.hpp"

Strategy::Strategy(): portfolio(1000), availableToBuy(true){
    
}

void Strategy::buy(string stockSymbol, int volume, double currentPrice){
    portfolio.buyStock(stockSymbol, volume, currentPrice);
    
}   

void Strategy::sell(string stockSymbol, int volume, double currentPrice){
    portfolio.sellStock(stockSymbol, volume, currentPrice);

}

int Strategy::getOrderVolume(){
    return orderVolume;
}
OrderType Strategy::waveRiding(string stockSymbol, double currentPrice, vector<minuteTickerInfo> dayInfo){
    this->dayInfo = dayInfo;

    if(dayInfo.size() == 1){
        peakOrDipPrice = dayInfo[0].close;
    }
    if(dayInfo.size() > 2){
        double mostRecentClosePrice = dayInfo.back().close;
        int totalPossibleBuyAmount = int (portfolio.getCashOnHand() / currentPrice);
        if(mostRecentClosePrice > peakOrDipPrice && availableToBuy){
            orderVolume = totalPossibleBuyAmount;
            buy(stockSymbol, totalPossibleBuyAmount, currentPrice);
            availableToBuy = false;
            return OrderType::MARKETBUY; 
        } else if (mostRecentClosePrice < peakOrDipPrice && !availableToBuy){
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
