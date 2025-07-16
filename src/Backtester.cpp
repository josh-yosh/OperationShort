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


Backtester::Backtester(int timeRatioMsToSec, string tickerSymbol, int simulatedYear, int simulatedMonth, int simulatedDay, bool timeEnd)
    : timeRatioMsToSec(timeRatioMsToSec), tickerSymbol(tickerSymbol), simulatedYear(simulatedYear), simulatedMonth(simulatedMonth), simulatedDay(simulatedDay), simulatedHour(13), simulatedMin(0), timeEnd(timeEnd)
{ //need to add algorithm in later as parameter
    startTime = steady_clock::now();
}

void Backtester::simulateMinute(string csvName){
    //msToVirtualSecond == value of variable is #ms per virtual simulated second.

    if(timeRatioSatifisfied() && !timeEnd){
        pushToDayInfo(pullMinuteTickerInfo(csvName));
    }

}

//time functions

auto Backtester::getElapsedTime(){
    auto end = steady_clock::now();
    auto start = this->startTime;
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

bool Backtester::timeRatioSatifisfied(){
    bool ratioSatisfied = ((this->getElapsedTime().count()%this->timeRatioMsToSec) == 0);
    return ratioSatisfied;
}

char* Backtester::getFullDate(){
    char* fullDate;
    //2025-07-11 13:35:00+00:00
    //year-month-day hour:minute:second+(hours offset of utc):(minutes offset of utc)
    int sizeOfFullDate = 26; //25 + null terminator
    snprintf(fullDate, 26, "%04d-%02d-%02d %02d:%02d:00+00:00", this->simulatedYear, this->simulatedMonth, this->simulatedDay, this->simulatedHour, this->simulatedMin);
    return fullDate;
}

//pulling market info functions

void Backtester::pushToDayInfo(minuteTickerInfo minuteInfo){
    this->dayInfo.push_back(minuteInfo); 
}

void Backtester::incrementSimulatedMinute(){
    if(simulatedHour == 20){
        timeEnd = true;
    }else if(simulatedMin == 59){
        simulatedHour++;
        simulatedMin = 0;
    } else {
        simulatedMin++;
    }
}

minuteTickerInfo Backtester::pullMinuteTickerInfo(string csvName){
    // File pointer
    fstream fin;

    //getting current time 
    string fullDate = this->getFullDate();

    // Open an existing file
    fin.open("APPL_Data.csv", ios::in);


    // Get the roll number
    // of which the data is required
    int count = 0;
    

    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line, word, temp;
    minuteTickerInfo minuteInfo;

    while (fin >> temp)
    {

        row.clear();

        // read an entire row and
        // store it in a string variable 'line'
        getline(fin, line);

        // used for breaking words
        stringstream s(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ','))
        {
            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }

        // Compare the roll number
        if (row[0] == fullDate)
        {
            // Print the found data
            count = 1;
            cout << "time: " << row[0] << " : \n";
            cout << "Close: " << row[1] << "\n";
            cout << "High: " << row[2] << "\n";
            cout << "Low: " << row[3] << "\n";
            cout << "Open: " << row[4] << "\n";
            cout << "Volume: " << row[5] << "\n";

            minuteInfo.time = row[0];
            minuteInfo.close = stod(row[1]);
            minuteInfo.high = stod(row[2]);
            minuteInfo.low = stod(row[3]);
            minuteInfo.open = stod(row[4]);
            minuteInfo.open = stod(row[5]);
            return minuteInfo;
        }
    }
    if (count == 0)
        cout << "Record not found\n";
    fin.close();

    return minuteInfo;
}


