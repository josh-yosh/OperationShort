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
    static ImFont* logText = io.Fonts->AddFontFromFileTTF("./fonts/ProggyClean.ttf", 16.0f);
    static ImFont* headerFont = io.Fonts->AddFontFromFileTTF("./fonts/ProggyClean.ttf", 36.0f);

    io.Fonts->Build();



    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        // myimgui.NewFrame();

         // feed inputs to dear imgui, start new frame
        ImGui::LoadIniSettingsFromDisk("../my_ui_layout.ini");
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // myimgui.Update();     
        
        //graph window

        //----------------------------------------------------------------------------

        ImGui::SetNextWindowSizeConstraints(ImVec2(1100,800), ImVec2(1100,800));
        ImGui::SetNextWindowPos(ImVec2(75, 0), ImGuiCond_Once);

        ImGui::Begin("Graph");

        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::BeginChild("Graph of Price", ImVec2(1085, 760), ImGuiChildFlags_Borders);
        


        ImGui::PopStyleColor();
        ImGui::EndChild();

        ImGui::End();


        //----------------------------------------------------------------------------

        ImGui::SetNextWindowSizeConstraints(ImVec2(325,800), ImVec2(325,800));   //changes window size constraing
        ImGui::SetNextWindowPos(ImVec2(1200, 0), ImGuiCond_Once);
        ImGui::Begin("Log");                          // Create a window called "Conan Logo" and append into it.

        ImGui::PushFont(defaultFont);
        // bool show_demo_window = false;
        // ImGui::ShowDemoWindow(&show_demo_window);

        // ImGui::ShowStyleEditor(&(ImGui::GetStyle()));
        ImGui::PushFont(headerFont);
        ImGui::Text("SYMBOL: APPL");
        ImGui::PopFont();
       

        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::BeginChild("Scrolling", ImVec2(300, 725), ImGuiChildFlags_Borders);

        ImGui::PopFont();
        ImGui::PushFont(logText);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
        for (int n = 0; n < 50; n++)
            ImGui::Text("%02d:%02d:%02d - 5 Shares APPLE @ 5.42", n, n, n);

        ImGui::PopStyleColor();
        ImGui::PopFont();

        ImGui::PopStyleColor();
        ImGui::PopStyleColor(); //poping child background
        ImGui::EndChild();

        ImGui::End();

        //----------------------------------------------------------------------------

        ImGui::SetNextWindowSizeConstraints(ImVec2(240,50), ImVec2(240,50));
        ImGui::SetNextWindowPos(ImVec2(920, 35), ImGuiCond_Once);
        bool p_open_false = false;
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

        ImGui::Begin("Profit and Loss", &p_open_false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        ImGui::PopStyleColor();

        ImGui::PushFont(headerFont);
        ImGui::Text("P/L:");
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
        ImGui::Text("$200.43");
        ImGui::PopStyleColor();

        ImGui::PopFont();

        ImGui::End();
        
        //----------------------------------------------------------------------------
        // myimgui.Render();
        ImGui::Render();
	    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    myimgui.Shutdown();
    return 0;
}
