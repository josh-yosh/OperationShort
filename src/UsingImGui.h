#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>

struct PlotPoint{
    int holding;
};

class UseImGui{
public:


    void Init(GLFWwindow* window, const char* glsl_version);
    void NewFrame();
    virtual void Update();
    void Render();
    void Shutdown();
    void graphWindow();
    void logWindow(ImFont* defaultFont, ImFont* headerFont, ImFont* logText);
    void plWindow(ImFont* headerFont);
    void makeGraph();
    void plotPoint(int xPosOfLeft, int yPosOfBottom, int xPosOfRight, int yPosOfTop);

private:
    vector<PlotPoint> allCurrentInfo;

}; 