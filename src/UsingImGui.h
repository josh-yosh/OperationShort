#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>
#include "backtester.hpp"

struct PlotPoint{
    int holding;
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
    

    ImGuiIO &io;

    static ImFont* defaultFont;
    static ImFont* headerFont;
    static ImFont* logText;
}; 