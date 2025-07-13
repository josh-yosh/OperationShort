#include <iostream>
using namespace std; 


enum OrderType
{
    MARKETBUY, MARKETSELL, LIMITBUY, LIMITSELL
}; 

enum Symbol
{
//AAPL, GOOG, ETC.
};

struct Position //represents an action/order made by the bot
{
    OrderType order; //either buying, selling, limiting
    int positionSize; 
    int individualPrice; 
    Symbol tickerSymbol; 

}; 


class Backtester //keep in mind market opens 9:30am EST and closes 4pm EST
{
     
    int currentTimeHour; 
    int currentTimeMin; 
    int currentTimeSec; 
    double stockPrice;
    Position position; 

    public: 
        Backtester(int, int, int, double); 
        double sendTickPrice(Symbol symbol); 
        void simulateNextSecond(); 
        void simulateNextMin(); 
        void simulateNextHour(); 
        int getCurrentTimeHour();
        int getCurrentTimeMin();
        int getCurrentTimeSec(); 
        int getCurrentTimeFull();  
        double sendSoldPrice(); 
        double sendBoughtPrice(); 
        

    
}; 

