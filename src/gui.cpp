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

    GLFWwindow* window = glfwCreateWindow(600, 600, "Backtester", NULL, NULL);
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
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    

    // Setup Platform/RendererBindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    //AddFontFromFileTTF(const char* filename, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);
    static ImFont* defaultFont = io.Fonts->AddFontDefault();
    static ImFont* bigFont = io.Fonts->AddFontFromFileTTF("./fonts/ProggyClean.ttf", 24.0f);
    io.Fonts->Build();


    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        // myimgui.NewFrame();

         // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // myimgui.Update();        
        ImGui::Begin("Graph");                          // Create a window called "Conan Logo" and append into it.

        ImGui::PushFont(defaultFont);
        bool show_demo_window = true;
        
        ImGui::ShowDemoWindow(&show_demo_window);
        ImGui::ShowStyleEditor(&(ImGui::GetStyle()));
        
        ImGui::Text("STOCK: ");
        ImGui::BeginChild("Scrolling");

        ImGui::PopFont();
        ImGui::PushFont(bigFont);
        for (int n = 0; n < 50; n++)
            ImGui::Text("%04d: Some text", n);

        ImGui::PopFont();
        ImGui::EndChild();

        ImGui::End();




        // myimgui.Render();
        ImGui::Render();
	    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    myimgui.Shutdown();
    return 0;
}
