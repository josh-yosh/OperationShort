#include "backtester.hpp"
#include "OrderTypeEnum.hpp"
#include <chrono>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std::chrono;
using namespace std;


Backtester::Backtester(int timeRatioMsToSec, string tickerSymbol, int simulatedYear, int simulatedMonth, int simulatedDay)
    : timeRatioMsToSec(timeRatioMsToSec), tickerSymbol(tickerSymbol), 
    simulatedYear(simulatedYear), simulatedMonth(simulatedMonth), simulatedDay(simulatedDay), simulatedHour(13), simulatedMin(30), 
    timeEnd(false), totalNumOfMinutes(0), dayMinimum(0.0), dayMaximum(0.0)
{ //need to add algorithm in later as parameter
    startTime = steady_clock::now();
}

void Backtester::simulateMinute(string csvName){
    //msToVirtualSecond == value of variable is #ms per virtual simulated second.

    
    if(timeRatioSatifisfied() && !timeEnd){
        pushToDayInfo(pullMinuteTickerInfo(csvName));
        this->incrementSimulatedMinute();
    }

}

//time functions

auto Backtester::getElapsedTime(){ //works
    auto end = steady_clock::now();
    auto start = this->startTime;
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

double Backtester::getDayMaximum(){
    return dayMaximum;
}

double Backtester::getDayMinimum(){
    return dayMinimum;
}

int Backtester::getTotalNumOfMinutes(){
    return totalNumOfMinutes;
}

double Backtester::getCurrentPrice(){
    cout << dayInfo.size() << "\n";
    return dayInfo.back().close;
}

void Backtester::setInitialMinAndMax(minuteTickerInfo tempTickerInfo){
    dayMinimum = tempTickerInfo.close - 2;
    dayMaximum = tempTickerInfo.close + 2;
}

bool Backtester::timeRatioSatifisfied(){ //works
    bool ratioSatisfied = ((getElapsedTime().count() > timeRatioMsToSec));
    if(ratioSatisfied){
        startTime = steady_clock::now();
    }
    return ratioSatisfied;
}

char* Backtester::getFullDate(){
    char* fullDate = (char*)malloc(sizeof(char) * 26);
    //2025-07-11 13:35:00+00:00
    //year-month-day hour:minute:second+(hours offset of utc):(minutes offset of utc)
    int sizeOfFullDate = 26; //25 + null terminator
    snprintf(fullDate, 26, "%04d-%02d-%02d %02d:%02d:00+00:00", this->simulatedYear, this->simulatedMonth, this->simulatedDay, this->simulatedHour, this->simulatedMin);
    return fullDate;
}

//pulling market info functions

void Backtester::pushToDayInfo(minuteTickerInfo minuteInfo){
    dayInfo.push_back(minuteInfo);
    // cout << "lol\n";
    if(minuteInfo.close > dayMaximum){
        dayMaximum = minuteInfo.close;
        // cout << "hit\n";
    }
    if(minuteInfo.close < dayMinimum){
        dayMinimum = minuteInfo.close;
        // cout << "double hit\n";
    }  
}

void Backtester::incrementSimulatedMinute(){
    if(totalNumOfMinutes < int (6.5 * 60))
        totalNumOfMinutes++;
    if(simulatedHour == 19 && simulatedMin == 59){
        timeEnd = true;
    }else if(simulatedMin == 59){
        simulatedHour++;
        simulatedMin = 0;
    } else {
        simulatedMin++;
    }
}

minuteTickerInfo Backtester::sendRecentMinuteTickerInfo(){
    return dayInfo.back();
}

vector<minuteTickerInfo> Backtester::getDayInfo(){
    return dayInfo;
}

minuteTickerInfo Backtester::pullMinuteTickerInfo(string csvName){
    // File pointer
    fstream fin;

    //getting current time 
    string fullDate = this->getFullDate();

    // Open an existing file
    fin.open("src/tickerData/AAPL_data.csv", ios::in);


    // Get the roll number
    // of which the data is required
    int count = 0;
    

    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line, word, temp;
    minuteTickerInfo minuteInfo;
    getline(fin, line); //get first line: Price,Close,High,Low,Open,Volume
    getline(fin, line); // getting passed second line: Ticker,AAPL,AAPL,AAPL,AAPL,AAPL;

    while (getline(fin, line))
    {
        
        
        row.clear();

        // used for breaking words
        stringstream ss(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        string substr;

        while (getline(ss, substr, ',')){
            
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

            // cout << "time: " <<  minuteInfo.time << " : \n";
            // cout << "Close: " << minuteInfo.close << "\n";
            // cout << "High: " << minuteInfo.high << "\n";
            // cout << "Low: " << minuteInfo.low << "\n";
            // cout << "Open: " << minuteInfo.open << "\n";

            if(dayMinimum == 0.0 || dayMaximum == 0.0){
                cout << "seting day min";
                setInitialMinAndMax(minuteInfo);
            }

            break;
        }


    }
    if (count == 0)
        cout << "Record not found\n";
    fin.close();

    return minuteInfo;
}



