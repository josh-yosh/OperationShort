#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>
#include "backtester.hpp"

struct PlotPoint{
    int holding;
};

struct orderMark{
    int timeOfOrder;
    double priceOfOrder;
    bool isBuyMark;
    string stockSymbol;
    string stringTimeOfOrder;
    int volume;


    orderMark(int timeOfOrder, double priceOfOrder, bool isBuyMark, string stockSymbol, string stringTimeOfOrder, int volume) : 
                timeOfOrder(timeOfOrder), priceOfOrder(priceOfOrder), isBuyMark(isBuyMark), 
                stockSymbol(stockSymbol), stringTimeOfOrder(stringTimeOfOrder), volume(volume){}
};

class UseImGui{
public:

    UseImGui(ImGuiIO &io);
    void Init(GLFWwindow* window, const char* glsl_version);
    void NewFrame();
    void Render();
    void Shutdown();
    void graphWindow(Backtester backtesterInstance, ImFont* timeText);
    void logWindow(ImFont* defaultFont, ImFont* headerFont, ImFont* logText, vector<minuteTickerInfo> tempDayInfo);
    void plWindow(ImFont* headerFont);
    void makeGraph(Backtester backtesterInstance, ImFont* timeText);
    void plotPoint(double high, double low, int numTicker, int dayMax, int dayMin, ImDrawList *draw_list, Backtester backtesterInstance);
    void drawCurrentPrice(int xPositionOfCandle ,int yCandleTop, Backtester backtesterInstance, ImFont* timeText);
    void makeOrderMark(orderMark orderMarkElement, int dayMin, ImDrawList *draw_list);
    void handleOrder(OrderType orderType, int totalNumOfMinutes, double currentPrice, string stockSymbol, string stringTimeOfOrder, int orderVolume);
    


private:
    int xPosOfYaxis;
    int yPosOfXaxis;
    int xPosOfXaxisEnd;
    int yPosOfYaxisEnd;
    int xNumOfIndents;
    int yNumOfIndents;
    int widthOfGraph;
    int heightOfGraph;
    int widthPixelsPerMinute;
    int heightPixelPerDollar;
    int numTicker;
    int xPositionOfCurrentPrice;
    int yPositionOfCurrentPrice;
    ImVec2 centerScreen;
    ImVec4 white;
    
    vector<orderMark> allOrderMarks;
    ImGuiIO &io;

    static ImFont* defaultFont;
    static ImFont* headerFont;
    static ImFont* logText;
}; 