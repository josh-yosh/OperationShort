#pragma once

#include <iostream>
#include "OrderTypeEnum.hpp"
#include <vector>
#include <chrono>
#include <string>


using namespace std; 


struct Position //represents an action/order made by the bot
{
    OrderType order; //either buying, selling, limiting
    int positionSize; 
    int individualPrice; 
    string tickerSymbol; 
}; 

struct minuteTickerInfo {
    double high;
    double low;
    double open;
    double close;
    string time;
};

class Backtester //keep in mind market opens 9:30am EST and closes 4pm EST
{
    

    public: 
        Backtester(int timeRatioMsToSec, string tickerSymbol, int year, int month, int day, int endDay); //will hold all the information such as starting time upon initialization

        void simulateMinute(); //if ratio has passed then add information to portfolio
        void pushToDayInfo(minuteTickerInfo minuteInfo); //pushed information to the vector which will be what the graph is made of

        minuteTickerInfo pullMinuteTickerInfo();
        
        vector<minuteTickerInfo> getDayInfo();
        double getDayMinimum();
        double getDayMaximum();
        int getTotalNumOfMinutes();
        char* getFullDate();
        auto getElapsedTime();
        double getCurrentPrice();
        char* getCurrentTime();
        string getTickerSymbol();
        bool getIsEnd();

        void setInitialMinAndMax(minuteTickerInfo tempTickerInfo);

        void setDayMinimum(double dayMin);
        void setDayMaximum(double dayMax);

        bool timeRatioSatifisfied();

        void incrementSimulatedMinute();
        minuteTickerInfo sendRecentMinuteTickerInfo();

        void calculateLargestPossibleProfit(double testCash);
        double getLargestPossibleProfit();

        void createDayInfoCSV(string tickerSymbol, int day, int month, int year);

        int getSimulatedHour();
        int getSimulatedMin();

    private:
        int simulatedYear;
        int simulatedMonth;
        int simulatedDay;
        int simulatedHour; 
        int simulatedMin;
        
        int endDay;

        int totalNumOfMinutes;

        double dayMinimum;
        double dayMaximum;

        int timeRatioMsToSec; 
        double stockPrice;
        bool timeEnd;
        double largestPossibleProfit;

        Position position; 
        string tickerSymbol;
        vector<minuteTickerInfo> dayInfo;
        std::chrono::steady_clock::time_point startTime;
}; 

