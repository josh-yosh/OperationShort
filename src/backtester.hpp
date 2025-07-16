#include <iostream>
#include "OrderTypeEnum.hpp"
#include "SymbolEnum.hpp"
#include <vector>
#include <chrono>
#include <string>


using namespace std; 


struct Position //represents an action/order made by the bot
{
    OrderType order; //either buying, selling, limiting
    int positionSize; 
    int individualPrice; 
    Symbol tickerSymbol; 
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
    int simulatedYear;
    int simulatedMonth;
    int simulatedDay;
    int simulatedHour; 
    int simulatedMin; 

    int timeRatioMsToSec; 
    double stockPrice;
    bool timeEnd;

    Position position; 
    Symbol tickerSymbol;
    vector<minuteTickerInfo> dayInfo;
    std::chrono::steady_clock::time_point startTime;

    public: 
        Backtester(int timeRatioMsToSec, Symbol tickerSymbol, int year, int month, int day, bool timeEnd); //will hold all the information such as starting time upon initialization

        void simulateMinute(string csvName); //if ratio has passed then add information to portfolio
        void pushToDayInfo(minuteTickerInfo minuteInfo); //pushed information to the vector which will be what the graph is made of

        minuteTickerInfo pullMinuteTickerInfo(string csvName); 

        char* getFullDate();

        auto getElapsedTime();
        bool timeRatioSatifisfied();

        void incrementSimulatedMinute();

    
}; 

