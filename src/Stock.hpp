#pragma once

#include <vector>
#include <string>

using namespace std;



class Stock{

    public:
        Stock(string name);

        void addPosition(int volume, double buyPrice);
        double sellPosition(int volume, double sellPrice);
        double getTotalStockPrice(double currentStockPrice);
        int getTotalVolume();
        double sellAll(double currentStockPrice);
        string getName();

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
        double totalProfitLoss;
        string name;
        string tickerSymbol;
};