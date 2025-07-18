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

    UseImGui();
    void Init(GLFWwindow* window, const char* glsl_version);
    void NewFrame();
    virtual void Update();
    void Render();
    void Shutdown();
    void graphWindow();
    void logWindow(ImFont* defaultFont, ImFont* headerFont, ImFont* logText);
    void plWindow(ImFont* headerFont);
    void makeGraph(Backtester backtesterInstance);
    void plotPoint(double high, double low, int numTicker, int dayMax, int dayMin, ImDrawList *draw_list);


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
    ImVec4 white;
}; 