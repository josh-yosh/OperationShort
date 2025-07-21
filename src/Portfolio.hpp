#pragma once

#include <vector>
#include "Stock.hpp"
#include "backtester.hpp"

using namespace std;

class Portfolio {

    public: 
        Portfolio(double cashOnHand);
        void sellStock(string stockSymbol, int volume, double currentPrice);
        void sellStockAll(string stockSymbol, double currentPrice);
        void buyStock(string stockSymbol, int volume,  double currentPrice);
        double getCashOnHand();
        void removeCash(double amount);
        void addCash(double amount);
        double getTotalValue(double currentPrice);
        vector<Stock> getStockList();
        void printStockList();
        int getStockCount(string stockSymbol);


    private:
        vector<Stock> stockPortfolio;
        double totalValue;
        double cashOnHand;
        double totalProfitLoss;
        const int notInPortfolio = -1;

        int findIndexOfStock(string stockSymbol);
};