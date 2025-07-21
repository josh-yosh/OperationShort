#pragma once

#include <vector>
#include "Portfolio.hpp"
#include "backtester.hpp"
#include <string>
#include <stdbool.h>
#include "OrderTypeEnum.hpp"

class Strategy{

    public:
        Strategy();
        void buy(string stockSymbol, int volume, double currentPrice);
        void sell(string stockSymbol, int volume, double currentPrice);
        OrderType waveRiding(string stockSymbol, double currentPrice, vector<minuteTickerInfo> dayInfo); 
        int getOrderVolume();

    private:
        Portfolio portfolio;
        vector<minuteTickerInfo> dayInfo;
        double previousCloseMinuteClose;
        bool availableToBuy;
        double peakOrDipPrice;
        int orderVolume;

       
};