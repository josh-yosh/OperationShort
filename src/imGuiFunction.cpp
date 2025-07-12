#include "UsingImGui.h"



void UseImGui::Init(GLFWwindow* window, const char* glsl_version){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    

    // Setup Platform/RendererBindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


};

void UseImGui::NewFrame(){
    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UseImGui::Update(){
    ImGui::Begin("Graph");                          // Create a window called "Conan Logo" and append into it.

    bool show_demo_window = true;

    ImGui::ShowDemoWindow(&show_demo_window);
    ImGui::ShowStyleEditor(&(ImGui::GetStyle()));
    ImGui::Text("STOCK: ");
    ImGui::BeginChild("Scrolling");
    for (int n = 0; n < 50; n++)
        ImGui::Text("%04d: Some text", n);
    ImGui::EndChild();

	ImGui::End();
};

void UseImGui::Render(){
    // Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};
void UseImGui::Shutdown(){
    // Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
};
