#include "backtester.hpp"


Backtester::Backtester(int hour, int min, int sec, double stockP)
{
    currentTimeHour = hour; 
    currentTimeMin = min; 
    currentTimeSec = sec; 
    stockPrice = stockP; 
}

double Backtester::sendTickPrice(Symbol symbol)
{
//need data
}

void Backtester::simulateNextSecond()
{
    currentTimeSec++; 
}
void Backtester::simulateNextMin()
{
    currentTimeMin++; 
}
void Backtester::simulateNextHour()
{
    currentTimeHour++; 
}
int Backtester::getCurrentTimeHour()
{
    return currentTimeHour; 
}
int Backtester::getCurrentTimeMin()
{  
    return currentTimeMin; 
}
int Backtester::getCurrentTimeSec()
{   
    return currentTimeSec; 
}
int Backtester::getCurrentTimeFull()
{
    //might not need
}
double Backtester::sendSoldPrice()
{
    return stockPrice;
}
double Backtester::sendBoughtPrice()
{
    return stockPrice; 
}

