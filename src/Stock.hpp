#pragma once

#include <vector>
#include <string>

using namespace std;



class Stock{

    public:
        Stock(string name);

        void addPosition(int volume, double buyPrice);
        double removePosition(int volume, double sellPrice);
        void printPositions();

        struct position{
            int volume;
            double buyPrice;

            position(int volume, double buyPrice) : 
                volume(volume), buyPrice(buyPrice){}
        };


    private:
        vector<position> positions;
        int totalVolume;
        double totalStockValue;
        double priceBasis;
        double totalStockGain;
        string name;
        string tickerSymbol;
};