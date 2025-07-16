#define GLFW_INCLUDE_NONE
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "UsingImGui.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <imgui.h>


using namespace std;


int main() {
    
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    const char *glsl_version = "#version 410";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(1200, 600, "Backtester", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); 

    // Initialize GLAD **after** context creation
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);

    UseImGui myimgui;
    // myimgui.Init(window, glsl_version);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    

    // Setup Platform/RendererBindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    //AddFontFromFileTTF(const char* filename, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);

    static ImFont* defaultFont = io.Fonts->AddFontDefault();
    static ImFont* headerFont = io.Fonts->AddFontFromFileTTF("./fonts/ProggyClean.ttf", 36.0f);
    static ImFont* logText = io.Fonts->AddFontFromFileTTF("./fonts/ProggyClean.ttf", 16.0f);
    
    io.Fonts->Build();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

         // feed inputs to dear imgui, start new frame
        ImGui::LoadIniSettingsFromDisk("../my_ui_layout.ini");

        myimgui.NewFrame();    
        

        //----------------------------------------------------------------------------

        myimgui.graphWindow();

        //----------------------------------------------------------------------------

        myimgui.logWindow(defaultFont, headerFont, logText);

        //----------------------------------------------------------------------------

        myimgui.plWindow(headerFont);
        
        //----------------------------------------------------------------------------
        myimgui.Render();

        //----------------------------------------------------------------------------
        glfwSwapBuffers(window);
    }

    myimgui.Shutdown();
    return 0;
}
