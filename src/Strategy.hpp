#pragma once

#include <vector>
#include "Portfolio.hpp"
#include "backtester.hpp"
#include <string>
#include <stdbool.h>
#include "OrderTypeEnum.hpp"

class Strategy{

    public:
        Strategy(double startingCash);
        void buy(string stockSymbol, int volume, double currentPrice);
        void sell(string stockSymbol, int volume, double currentPrice);
        OrderType waveRiding(string stockSymbol, double currentPrice, vector<minuteTickerInfo> dayInfo); 
        int getOrderVolume();
        void setOrderVolume(int orderVolume);
        Portfolio getPortfolio();
        double getStartingCash();

    private:
        Portfolio portfolio;
        vector<minuteTickerInfo> dayInfo;
        double previousCloseMinuteClose;
        bool availableToBuy;
        double peakOrDipPrice;
        int orderVolume;
        double startingCash;

       
};