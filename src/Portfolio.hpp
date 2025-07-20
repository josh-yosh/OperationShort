#pragma once

#include <vector>
#include "Stock.hpp"
#include "backtester.hpp"

using namespace std;

class Portfolio {

    public: 
        Portfolio(double cashOnHand);
        void sellStock(string stockSymbol, int volume, Backtester backtesterInstance);
        void sellStockAll(string stockSymbol, Backtester backtesterInstance);
        void buyStock(string stockSymbol, int volume, Backtester backtesterInstance);
        double getCashOnHand();
        void removeCash(double amount);
        void addCash(double amount);
        double getTotalValue(Backtester backtesterInstance);
        vector<Stock> getStockList();
        void printStockList();

    private:
        vector<Stock> stockPortfolio;
        double totalValue;
        double cashOnHand;
        double totalProfitLoss;

        int findIndexOfStock(string stockSymbol);
};