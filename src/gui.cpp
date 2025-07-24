#define GLFW_INCLUDE_NONE
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "UsingImGui.h"
#include "backtester.hpp"
#include "Strategy.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <imgui.h>


using namespace std;


int main() {
    
    //initializes GLFW ----------------------------------------------------------
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    //looks for minimum veresion -------------------------------------------------

    const char *glsl_version = "#version 410";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // creates GLFW WINDOW ------------------------------------------------------

    GLFWwindow* window = glfwCreateWindow(2400, 1000, "Backtester", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // creating context for window ----------------------------------------------

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); 


    // Initialize GLAD **after** context creation
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // creating context for window ----------------------------------------------

    int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);

    //setting up context, io, and  myimgui object -------------------------------

    

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    
    UseImGui myimgui(io);

    // Setup Platform/RendererBindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    //---------------------------------------------------------------------------
    //AddFontFromFileTTF(const char* filename, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);

    static ImFont* defaultFont = io.Fonts->AddFontDefault();
    static ImFont* headerFont = io.Fonts->AddFontFromFileTTF("./fonts/ProggyClean.ttf", 36.0f);
    static ImFont* logText = io.Fonts->AddFontFromFileTTF("./fonts/ProggyClean.ttf", 16.0f);
    static ImFont* timeText = io.Fonts->AddFontFromFileTTF("./fonts/ProggyClean.ttf", 24.0f);
    
    io.Fonts->Build();

    //backtester instance---------------------------------------------------------
    //ms ratio, symbol, year, month, day
    Backtester backtesterInstance(10, "APPL", 2025, 7, 22);
    Strategy strategyInstance;
    strategyInstance.setOrderVolume(4);

    //while loop ---------------------------------------------------------

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

         // feed inputs to dear imgui, start new frame
        ImGui::LoadIniSettingsFromDisk("../my_ui_layout.ini");        
        //----------------------------------------------------------------------------

        backtesterInstance.simulateMinute("APPL");
        vector<minuteTickerInfo> tempDayInfo = backtesterInstance.getDayInfo();

        OrderType order = strategyInstance.waveRiding("APPL", backtesterInstance.getCurrentPrice(), backtesterInstance.getDayInfo());
        myimgui.handleOrder(order, backtesterInstance.getTotalNumOfMinutes(), backtesterInstance.getCurrentPrice(), backtesterInstance.getTickerSymbol(),  backtesterInstance.getCurrentTime(), strategyInstance.getOrderVolume());
        
        
        //----------------------------------------------------------------------------
        // myimgui.NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        

        //----------------------------------------------------------------------------
        myimgui.graphWindow(backtesterInstance, timeText, strategyInstance);
       

        //----------------------------------------------------------------------------

        myimgui.logWindow(defaultFont, headerFont, logText, tempDayInfo);

        //----------------------------------------------------------------------------
        myimgui.plWindow(headerFont, strategyInstance.getPortfolio().getTotalProfitLoss());

        
        //----------------------------------------------------------------------------
        myimgui.Render();

        //----------------------------------------------------------------------------
        glfwSwapBuffers(window);
    }

    myimgui.Shutdown();
    return 0;
}
