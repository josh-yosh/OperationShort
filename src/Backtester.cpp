#include "backtester.hpp"
#include "OrderTypeEnum.hpp"
#include <chrono>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <Python.h>
#include <iomanip>


using namespace std::chrono;
using namespace std;

//constructor for backtester object
Backtester::Backtester(int timeRatioMsToSec, string tickerSymbol, int simulatedYear, int simulatedMonth, int simulatedDay, int endDay)
    : timeRatioMsToSec(timeRatioMsToSec), tickerSymbol(tickerSymbol), 
    simulatedYear(simulatedYear), simulatedMonth(simulatedMonth), simulatedDay(simulatedDay), simulatedHour(13), simulatedMin(30), endDay(endDay),
    timeEnd(false), totalNumOfMinutes(0), dayMinimum(0.0), dayMaximum(0.0), 
    stockPrice(0.0), position(), dayInfo(), 
    largestPossibleProfit(0.0)
{ //need to add algorithm in later as parameter
    startTime = steady_clock::now();
}

//is used to simulate a single minute
void Backtester::simulateMinute(){
    //msToVirtualSecond == value of variable is #ms per virtual simulated second.

    if(timeRatioSatifisfied() && !timeEnd){ //time end is a variable to see if we reached the end of the day
        pushToDayInfo(pullMinuteTickerInfo());//pushing the pulled minute into backtester variable
        this->incrementSimulatedMinute();
    }

}

string Backtester::getTickerSymbol(){
    return tickerSymbol;
}

//time functions

auto Backtester::getElapsedTime(){ //to see how much time has passed since the last simulated minute
    auto end = steady_clock::now();
    auto start = this->startTime;
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

double Backtester::getDayMaximum(){ //day maximum value, starts as first minute close value +2 dollars
    return dayMaximum;
}

double Backtester::getDayMinimum(){ //day minimum value, starts as first minute close value -2 dollars
    return dayMinimum;
}

int Backtester::getTotalNumOfMinutes(){ //total minutes passed since the beginning, can be thought of #of step
    return totalNumOfMinutes;
}

double Backtester::getCurrentPrice(){ //most recenet minute info's close price
    return dayInfo.back().close;
}

bool Backtester::getIsEnd(){
    return timeEnd;
}

void Backtester::setInitialMinAndMax(minuteTickerInfo tempTickerInfo){ 
    dayMinimum = tempTickerInfo.close - 2; //sets the first close as the middle price
    dayMaximum = tempTickerInfo.close + 2;
}

void Backtester::setDayMinimum(double dayMin){
    dayMinimum = dayMin;
}

void Backtester::setDayMaximum(double dayMax){
    dayMaximum = dayMax;
}

bool Backtester::timeRatioSatifisfied(){ //if the elapsed time from the last simulated minute is less than the time ratio then it runs
    bool ratioSatisfied = ((getElapsedTime().count() > timeRatioMsToSec));
    if(ratioSatisfied){
        startTime = steady_clock::now(); //resets clock 
    }
    return ratioSatisfied;
}

char* Backtester::getFullDate(){ //returns full day to search for in the database
    char* fullDate = (char*)malloc(sizeof(char) * 26);
    //2025-07-11 13:35:00+00:00
    //year-month-day hour:minute:second+(hours offset of utc):(minutes offset of utc)
    int sizeOfFullDate = 26; //25 + null terminator
    snprintf(fullDate, 26, "%04d-%02d-%02d %02d:%02d:00+00:00", this->simulatedYear, this->simulatedMonth, this->simulatedDay, this->simulatedHour, this->simulatedMin);
    return fullDate;
}

char* Backtester::getCurrentTime(){ //returns just the hour and minute time for the y axis and time portions. j
    char* currentTime = (char*)malloc(sizeof(char) * 6);

    snprintf(currentTime, 6, "%02d:%02d", simulatedHour, simulatedMin);
    return currentTime;
}

//pulling market info functions

void Backtester::pushToDayInfo(minuteTickerInfo minuteInfo){ //pushes the minute info to day info
    dayInfo.push_back(minuteInfo);
}

//DOESN'T WORK WITH DAYS THAT GO INBETWEEN MONTHS
void Backtester::incrementSimulatedMinute(){ //for the internal clock
    if(totalNumOfMinutes < int (6.5 * 60))
        totalNumOfMinutes++;
    if(simulatedHour == 19 && simulatedMin == 59){ //finishes at time 19:59

        simulatedDay++;
        if(simulatedDay == endDay + 1){ //if last day, timeEnd
            timeEnd = true;
        } else {
            simulatedHour = 13;
            simulatedMin = 30;
            dayInfo.clear();
            totalNumOfMinutes = 0;

            //first value
            pushToDayInfo(pullMinuteTickerInfo());//pushing the pulled minute into backtester variable
            this->incrementSimulatedMinute();
        }
    }else if(simulatedMin == 59){ //not end of the day but end of hour
        simulatedHour++;
        simulatedMin = 0;
    } else {
        simulatedMin++; //not end of day or hour
    }
}

minuteTickerInfo Backtester::sendRecentMinuteTickerInfo(){
    return dayInfo.back();
}

vector<minuteTickerInfo> Backtester::getDayInfo(){
    return dayInfo;
}

minuteTickerInfo Backtester::pullMinuteTickerInfo(){
    // File pointer
    fstream fin; 

    //getting current time 
    string fullDate = this->getFullDate();

    // Open an existing file
    std::stringstream file;
    file << "src/tickerData/" << tickerSymbol << "_"
        << simulatedYear << "-"
        << std::setw(2) << std::setfill('0') << simulatedMonth << "-"
        << std::setw(2) << std::setfill('0') << simulatedDay << "_data.csv";
    
    
    std::string fileName = file.str();
    fin.open(fileName, ios::in);


    // Get the roll number
    // of which the data is required
    int count = 0;
    

    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line;
    minuteTickerInfo minuteInfo;
    getline(fin, line); //get first line: Price,Close,High,Low,Open,Volume
    getline(fin, line); // getting passed second line: Ticker,AAPL,AAPL,AAPL,AAPL,AAPL;

    while (getline(fin, line)) //gets ,,,,, portion of csv
    {
        row.clear();

        // used for breaking words
        stringstream ss(line);

        string substr;

        while (getline(ss, substr, ',')){ //seperates by comma's
            
            // add all the column data
            // of a row to a vector
            row.push_back(substr);
        }

        
        // Compare the roll number
        if (row[0] == fullDate)
        {
            // Print the found data
            count = 1;

            minuteInfo.time = row[0];
            minuteInfo.close = stod(row[1]);
            minuteInfo.high = stod(row[2]);
            minuteInfo.low = stod(row[3]);
            minuteInfo.open = stod(row[4]);


            //sets initial min and max, changes daymin and max if the highs or lows are lower than the current 
            //mins and maxes
            if(dayMinimum == 0.0 || dayMaximum == 0.0){ 
                setInitialMinAndMax(minuteInfo);
            }
            if(minuteInfo.high > dayMaximum){
                setDayMaximum(minuteInfo.high);
            }
            if(minuteInfo.low < dayMinimum){
                setDayMinimum(minuteInfo.low);
            }

            break;
        }


    }
    if (count == 0 && dayInfo.size()){
        minuteInfo.close = dayInfo.back().close;
        minuteInfo.high = dayInfo.back().high;
        minuteInfo.low = dayInfo.back().low;
        minuteInfo.open = dayInfo.back().open;
    }
        
    fin.close();

    return minuteInfo;
}




void Backtester::calculateLargestPossibleProfit(double testCash){
    double dip;
    double peak;
    bool climbing;
    int volume = testCash/dayInfo[0].close;
    double cashMade = 0;

    //initial set up
    if(dayInfo[1].high > dayInfo[0].high){
        dip = dayInfo[0].low;
        peak = dayInfo[1].high;
        climbing = true;
        volume = testCash/dayInfo[0].close;
    } else {
        peak = dayInfo[0].high;
        dip = dayInfo[1].low;
        climbing = false;
        cashMade = testCash;
    }

    for(int indexMinute = 1; indexMinute < dayInfo.size() - 1; indexMinute++){
        if(dayInfo[indexMinute + 1].high > dayInfo[indexMinute].high){
            peak = dayInfo[indexMinute + 1].high;
            
            if(!climbing){
                dip = dayInfo[indexMinute].low;
                climbing = true;
                volume = cashMade/dayInfo[indexMinute].low;
                cashMade -= volume*dayInfo[indexMinute].high;
            }

        } else {

            if(climbing){
                largestPossibleProfit += (peak - dip) * volume;
                peak = dayInfo[indexMinute].high;
                climbing = false;
                cashMade += volume * dayInfo[indexMinute].high;
            }
        }
    }

    if(climbing){
        cashMade += volume * dayInfo[dayInfo.size()].high;
    }

}

double Backtester::getLargestPossibleProfit(){
    return largestPossibleProfit;
}

void Backtester::createDayInfoCSV(string tickerSymbol, int day, int month, int year){
    Py_Initialize();

    PyRun_SimpleString("print('Hello from Python!')");

    // Example: call a function from a Python file
    PyObject *pName = PyUnicode_FromString("your_script");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != nullptr) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "your_function");
        if (PyCallable_Check(pFunc)) {
            PyObject *pValue = PyObject_CallObject(pFunc, nullptr);
            // You can now extract data from pValue if needed
            Py_DECREF(pValue);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }

    Py_Finalize();

}

int Backtester::getSimulatedHour(){
    return simulatedHour;
}
int Backtester::getSimulatedMin(){
    return simulatedMin;
}