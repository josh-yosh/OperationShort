#include "UsingImGui.h"
#include <iostream>


void UseImGui::Init(GLFWwindow* window, const char* glsl_version){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    

   
};

void UseImGui::NewFrame(){
    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UseImGui::graphWindow(){
    ImGui::SetNextWindowSizeConstraints(ImVec2(1100,800), ImVec2(1100,800));
    ImGui::SetNextWindowPos(ImVec2(75, 0), ImGuiCond_Once);

    ImGui::Begin("Graph");

    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    ImGui::BeginChild("Graph of Price", ImVec2(1085, 760), ImGuiChildFlags_Borders);
    


    ImGui::PopStyleColor();
    ImGui::EndChild();

    ImGui::End();
}

void UseImGui::logWindow(ImFont* defaultFont, ImFont* headerFont, ImFont* logText){

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
}

void UseImGui::plWindow(ImFont* headerFont){
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

void UseImGui::makeGraph(){
    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    
    int xPosOfLeft = 125;
    int yPosOfBottom = 725;
    int xPosOfRight = 1150;
    int yPosOfTop = 50;
    int xNumOfIndents = 13;
    int yNumOfIndents = 5;

    ImVec2 bottomLeftCorner(xPosOfLeft, yPosOfBottom);  //veritcal line = 675
    ImVec2 bottomRightCorner(xPosOfRight, yPosOfBottom); //horizontal line = 1025 long
    ImVec2 topLeftCorner(xPosOfLeft,yPosOfTop);

    ImVec4 white(1.0f, 1.0f, 1.0f, 1.0f);

    //for the little indents 
    
    int widthBetweenIndents = (xPosOfRight-xPosOfLeft)/xNumOfIndents;
    int xPosOfIndent = xPosOfLeft;

    int heightBetweenIndents = (yPosOfBottom-yPosOfTop)/yNumOfIndents;
    int yPosOfIndent = yPosOfBottom;

    // ImVec2 topOfIndent()

    draw_list->AddLine(bottomLeftCorner, bottomRightCorner, ImColor(white), 3.0f);
    draw_list->AddLine(bottomLeftCorner, topLeftCorner, ImColor(white), 3.0f);

    // 13 half hours in a market order

    for(int indentNum = 1; indentNum <= xNumOfIndents; indentNum++){

        ImVec2 topIndent(xPosOfIndent + widthBetweenIndents*(indentNum), (yPosOfBottom + 10));
        ImVec2 bottomIndent(xPosOfIndent + widthBetweenIndents*(indentNum), (yPosOfBottom - 10));

        draw_list->AddLine(topIndent, bottomIndent, ImColor(white), 3.0f);
    }

    for(int indentNum = 1; indentNum <= yNumOfIndents; indentNum++){

        ImVec2 leftIndent((xPosOfLeft - 10), yPosOfBottom - heightBetweenIndents*(indentNum));
        ImVec2 rightIndent((xPosOfLeft + 10), yPosOfBottom - heightBetweenIndents*(indentNum));

        draw_list->AddLine(leftIndent, rightIndent, ImColor(white), 3.0f);
    }
}

void UseImGui::plotPoint(int xPosOfLeft, int yPosOfBottom, int xPosOfRight, int yPosOfTop){
    int widthOfGraph = xPosOfRight - xPosOfLeft;
    int heightOfGraph = yPosOfBottom - yPosOfTop;
    int pixelsPerMinute = widthOfGraph / (int (6.5 * 60));

}
