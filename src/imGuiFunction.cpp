#include "UsingImGui.h"
#include <iostream>
#include "Strategy.hpp"

bool UseImGui::scrollToBottom = false;

void UseImGui::Init(GLFWwindow* window, const char* glsl_version){ 
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
};

UseImGui::UseImGui(ImGuiIO &io): io(io) {
    //graph coordinatnes
    xPosOfYaxis = 5;
    yPosOfXaxis = 725;
    xPosOfXaxisEnd = 1175;
    yPosOfYaxisEnd = 50;
    xNumOfIndents = 13;
    widthOfGraph = xPosOfXaxisEnd - xPosOfYaxis;
    heightOfGraph = yPosOfXaxis - yPosOfYaxisEnd;
    widthPixelsPerMinute = widthOfGraph / (int (6.5 * 60));
    
    
    static ImFont* defaultFont = io.Fonts->AddFontDefault();
    static ImFont* headerFont = io.Fonts->AddFontFromFileTTF("./fonts/ProggyClean.ttf", 36.0f);
    static ImFont* logText = io.Fonts->AddFontFromFileTTF("./fonts/ProggyClean.ttf", 16.0f);

    // cout << widthOfGraph << "\n";
    // cout << int (6.5 * 60) << "\n";
    // cout <<widthPixelsPerMinute << "\n";
    
}

void UseImGui::NewFrame(){
    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UseImGui::graphWindow(Backtester backtesterInstance, ImFont* timeText, ImFont* headerFont, Strategy strategyInstance){
    ImGui::SetNextWindowSizeConstraints(ImVec2(1225,850), ImVec2(1225,850)); //window size
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once); //window posisiotn

    ImGui::Begin("Graph");

    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    ImGui::BeginChild("Graph of Price", ImVec2(1200, 800), ImGuiChildFlags_Borders);
    makeGraph(backtesterInstance, timeText); //makes the graph

    //making top legend thing -------------------------------------------
    ImGui::SetCursorPos(ImVec2(30, 20));
    ImGui::PushFont(timeText);
    ImGui::Text("Time: %s", backtesterInstance.getCurrentTime());

    ImGui::SetCursorPos(ImVec2(200, 20));
    ImGui::Text("Current Price $%f", backtesterInstance.getCurrentPrice());
    ImGui::PopFont();

    plWindow(headerFont, strategyInstance.getPortfolio().getTotalProfitLoss());
    
    ImGui::PopStyleColor();
    ImGui::EndChild();

    //--------------------------------------------------------------------

    ImGui::End();
}

void UseImGui::logWindow(ImFont* defaultFont, ImFont* headerFont, ImFont* logText, vector<minuteTickerInfo> tempDayInfo){

   ImGui::SetNextWindowSizeConstraints(ImVec2(315,800), ImVec2(315,800));   //changes window size constraing
        ImGui::SetNextWindowPos(ImVec2(1225, 0), ImGuiCond_Once);
        ImGui::Begin("Log");                       

        ImGui::PushFont(defaultFont);

        ImGui::PushFont(headerFont);
        ImGui::Text("SYMBOL: APPL");
        ImGui::PopFont();
        
        

        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f)); //background color
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));  //border color
        ImGui::BeginChild("Scrolling", ImVec2(300, 725), ImGuiChildFlags_Borders || ImGuiWindowFlags_AlwaysVerticalScrollbar); 

        ImGui::PopFont();
        ImGui::PushFont(logText);

        //logs -------------------------------------------------------------------

        for (int i = 0; i < allOrderMarks.size(); i++){
            ImVec4 color;
            centerScreen = ImGui::GetCursorScreenPos();

            if(allOrderMarks[i].isBuyMark){
                color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // green
            } else {
                color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); //red
            }
            ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::Text( "%s - %d Shares %s @ %05f", allOrderMarks[i].stringTimeOfOrder.c_str(), allOrderMarks[i].volume, allOrderMarks[i].stockSymbol.c_str(), allOrderMarks[i].priceOfOrder);
            ImGui::PopStyleColor();
        }

        if (scrollToBottom){ //if newly added, scroll to bottom, then stop scrolling until next added item
            ImGui::SetScrollHereY(1.0f);
            scrollToBottom = false;
        }

        //logs -------------------------------------------------------------------


        ImGui::PopFont();
        

        ImGui::PopStyleColor();
        ImGui::PopStyleColor(); //poping child background
        ImGui::EndChild();

        ImGui::End();
}

void UseImGui::plWindow(ImFont* headerFont, double currentProfitLoss){

     ImVec4 color;
    centerScreen = ImGui::GetCursorScreenPos();

    //if profit/loss is neg, then red. if pos then green
    if(currentProfitLoss > 0){
        color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // green
    } else {
        color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); //red
    }

    ImGui::SameLine();
    ImGui::SetCursorPos(ImVec2(915, 5));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    ImGui::BeginChild("Profit and Loss", ImVec2(225, 50), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
    ImGui::PopStyleColor();

    ImGui::PushFont(headerFont);
    ImGui::Text("P/L:");
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Text, (color));
    ImGui::Text("$%02.2f", currentProfitLoss);
    ImGui::PopStyleColor();

    ImGui::PopFont();

    ImGui::EndChild();
}

void UseImGui::Render(){
    // Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UseImGui::Shutdown(){
    // Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
};

void UseImGui::makeGraph(Backtester backtesterInstance, ImFont* timeText){
    //coordinatnes
    centerScreen = ImGui::GetCursorScreenPos();
    xPosOfYaxis = 5 + centerScreen.x;
    yPosOfXaxis = 725 + centerScreen.y;
    xPosOfXaxisEnd = 1175 + centerScreen.x;
    yPosOfYaxisEnd = 50 + centerScreen.y;

    int hour = 13;
    int minute = 30;

    double dayMin = backtesterInstance.getDayMinimum();
    double dayMax = backtesterInstance.getDayMaximum();

    ImVec2 bottomLeftCorner(xPosOfYaxis, yPosOfXaxis);  //veritcal line = 675
    ImVec2 bottomRightCorner(xPosOfXaxisEnd, yPosOfXaxis); //horizontal line = 1025 long
    ImVec2 topLeftCorner(xPosOfYaxis,yPosOfYaxisEnd);
    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    
    ImVec4 white(1.0f, 1.0f, 1.0f, 1.0f);


    //for the little indents 

    double dayMaxAndMinDifference = (backtesterInstance.getDayMaximum() - backtesterInstance.getDayMinimum());

    numTicker = backtesterInstance.getTotalNumOfMinutes();
    if(numTicker < 2 ){
        dayOrderMarks.clear();
    }
    
    //ratio for dollar per pixel
    heightPixelPerDollar = (heightOfGraph/(backtesterInstance.getDayMaximum() - backtesterInstance.getDayMinimum())); 

    yNumOfIndents = int (dayMaxAndMinDifference);

    int widthBetweenIndents = (xPosOfXaxisEnd-xPosOfYaxis)/xNumOfIndents;
    int xPosOfIndent = xPosOfYaxis;

    int heightBetweenIndents = ((yPosOfXaxis-yPosOfYaxisEnd)/dayMaxAndMinDifference);
    int yPosOfIndent = yPosOfXaxis;

    // ImVec2 topOfIndent()

    draw_list->AddLine(bottomLeftCorner, bottomRightCorner, ImColor(white), 3.0f);
    draw_list->AddLine(bottomLeftCorner, topLeftCorner, ImColor(white), 3.0f);

    // 13 half hours in a market order
    // x axis marking
    for(int indentNum = 1; indentNum <= xNumOfIndents; indentNum++){

        ImVec2 topIndent(xPosOfIndent + widthBetweenIndents*(indentNum), (yPosOfXaxis + 10));
        ImVec2 bottomIndent(xPosOfIndent + widthBetweenIndents*(indentNum), (yPosOfXaxis - 10));

        hour = (13 + int((minute +(indentNum * 30))/60));
        minute = ((30 + (indentNum * 30))%60);

        ImVec2 bottomThinLine(xPosOfIndent + widthBetweenIndents*(indentNum), (yPosOfXaxis));
        ImVec2 topThinLine(xPosOfIndent + widthBetweenIndents*(indentNum), (yPosOfYaxisEnd));

        draw_list->AddLine(bottomThinLine, topThinLine, ImColor(white), 0.1f);

        const ImVec2 textOffset(-20, 25);

        //setCursoPos already takes into account of the window moving, we have to remove the added amount that is incorporated into
        //xPosOfIndent and yPosOfXaxis
        ImGui::SetCursorPos(ImVec2(((xPosOfIndent - centerScreen.x) + widthBetweenIndents*(indentNum)) + textOffset.x, ((yPosOfXaxis - centerScreen.y) + textOffset.y)));
        ImGui::PushFont(timeText);
        ImGui::Text("%d:%02d", hour, minute);
        ImGui::PopFont();

        draw_list->AddLine(topIndent, bottomIndent, ImColor(white), 3.0f);
    }

    // y axis markings

    for(int indentNum = 1; indentNum <= yNumOfIndents; indentNum++){

        ImVec2 leftIndent((xPosOfYaxis - 10), yPosOfXaxis - heightBetweenIndents*(indentNum));
        ImVec2 rightIndent((xPosOfYaxis + 10), yPosOfXaxis - heightBetweenIndents*(indentNum));

        draw_list->AddLine(leftIndent, rightIndent, ImColor(white), 3.0f);
    }

    // graph plotting for each minute high and low
    for(int minuteInfoIndex = 0; minuteInfoIndex < numTicker; minuteInfoIndex++){
        vector<minuteTickerInfo> tempInfo = backtesterInstance.getDayInfo();

        double minuteHigh = (tempInfo[minuteInfoIndex]).high;
        double minuteLow = (tempInfo[minuteInfoIndex]).low;
        plotPoint(minuteHigh, minuteLow, minuteInfoIndex, dayMax, dayMin, draw_list, backtesterInstance);
        
    }

    for(int markIndex = 0; markIndex < dayOrderMarks.size(); markIndex++){
        makeOrderMark(dayOrderMarks[markIndex], dayMin, draw_list);
    }
}

void UseImGui::plotPoint(double high, double low, int minuteInfoIndex, double dayMax, double dayMin, ImDrawList *draw_list, Backtester backtesterInstance){
    ImVec4 white(1.0f, 1.0f, 1.0f, 1.0f);
    int xPositionOfCandle = xPosOfYaxis + (widthPixelsPerMinute * minuteInfoIndex);
    int yCandleTop = yPosOfXaxis - (heightPixelPerDollar * (high - dayMin));
    int yCandleBottom = yPosOfXaxis - (heightPixelPerDollar * (low - dayMin));

    xPositionOfCurrentPrice = xPositionOfCandle;
    yPositionOfCurrentPrice = yCandleTop;

    ImVec2 topCandle(xPositionOfCandle, (yCandleTop));
    ImVec2 bottomCandle(xPositionOfCandle, (yCandleBottom));
   
    draw_list->AddLine(topCandle, bottomCandle, ImColor(white), 2.0f);
}

void UseImGui::makeOrderMark(orderMark orderMarkElement, double dayMin, ImDrawList *draw_list){
    ImVec4 color;
    centerScreen = ImGui::GetCursorScreenPos();

    if(orderMarkElement.isBuyMark){
        color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // green
    } else {
        color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); //red
    }

    const int xIndexDifference = 5;
    int yPositionOfIndent = yPosOfXaxis - (heightPixelPerDollar * (orderMarkElement.priceOfOrder - dayMin));
    int leftIndentX = xPosOfYaxis + (widthPixelsPerMinute * orderMarkElement.timeOfOrder) - xIndexDifference;
    int rightIndentX = xPosOfYaxis + (widthPixelsPerMinute * orderMarkElement.timeOfOrder) + xIndexDifference;

    ImVec2 leftIndent((leftIndentX), (yPositionOfIndent));
    ImVec2 rightIndent((rightIndentX), (yPositionOfIndent));

    draw_list->AddLine(leftIndent, rightIndent, ImColor(color), 2.0f);
}

void UseImGui::handleOrder(OrderType orderType, int totalNumOfMinutes, double currentPrice, string stockSymbol, string stringTimeOfOrder, int orderVolume) {
    switch (orderType) {
        case OrderType::MARKETBUY:
            allOrderMarks.push_back(orderMark(totalNumOfMinutes, currentPrice, true, stockSymbol, stringTimeOfOrder, orderVolume));
            dayOrderMarks.push_back(orderMark(totalNumOfMinutes, currentPrice, true, stockSymbol, stringTimeOfOrder, orderVolume));
            scrollToBottom = true;
            break;
        case OrderType::MARKETSELL:
            allOrderMarks.push_back(orderMark(totalNumOfMinutes, currentPrice, false, stockSymbol, stringTimeOfOrder, orderVolume));
            dayOrderMarks.push_back(orderMark(totalNumOfMinutes, currentPrice, false, stockSymbol, stringTimeOfOrder, orderVolume));
            scrollToBottom = true;
            break;
        case OrderType::LIMITBUY:
            break;
        case OrderType::LIMITSELL:
            break;
        case OrderType::NO_ORDER:
            break;
    }
}

void UseImGui::scoreScreen(ImFont* headerFont, Strategy strategyInstance, Backtester backtesterInstance){
    double percentReturn = (strategyInstance.getPortfolio().getTotalProfitLoss()/strategyInstance.getStartingCash()) * 100;
    double profitLoss = strategyInstance.getPortfolio().getTotalProfitLoss();
    double totalPossibleProfit = backtesterInstance.getLargestPossibleProfit();

    ImVec4 colorForPercent;
    ImVec4 colorForProfitAndLoss;
    ImVec4 green = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // green
    centerScreen = ImGui::GetCursorScreenPos();

    //if profit/loss is neg, then red. if pos then green
    if(percentReturn > 0){
        colorForPercent = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // green
    } else {
        colorForPercent = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); //red
    }

    if(profitLoss > 0){
        colorForProfitAndLoss = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // green
    } else {
        colorForProfitAndLoss = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); //red
    }

    ImGui::SetNextWindowSizeConstraints(ImVec2(620, 260), ImVec2(620, 260));   //changes window size constraing
        ImGui::SetNextWindowPos(ImVec2(400, 200), ImGuiCond_Once);
        ImGui::Begin("Final Score", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar); //make in middle
        
        
        ImGui::SetCursorPos(ImVec2(30, 20));
        ImGui::PushFont(headerFont);
        ImGui::Text("Final Score:");


        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::BeginChild("Result Screen", ImVec2(605, 180), true, ImGuiChildFlags_Borders | ImGuiWindowFlags_NoScrollbar);


        ImGui::PushStyleColor(ImGuiCol_Text, colorForPercent);
        ImGui::SetCursorPos(ImVec2(10, 10));
        ImGui::Text("Percent Return: %%%f", percentReturn);
        ImGui::PopStyleColor();

        ImGui::PushStyleColor(ImGuiCol_Text, colorForProfitAndLoss);
        ImGui::SetCursorPos(ImVec2(10, 50));
        ImGui::Text("Dollar Return: $%02.2f", profitLoss);
        ImGui::PopStyleColor();

        ImGui::PushStyleColor(ImGuiCol_Text, colorForProfitAndLoss);
        ImGui::SetCursorPos(ImVec2(10, 90));
        ImGui::Text("Total Possible Profit: $%02.2f", totalPossibleProfit);

        ImGui::SetCursorPos(ImVec2(10, 130));
        ImGui::Text("%% of Possible Profit: %%%.4f", (profitLoss/totalPossibleProfit) * 100);


        ImGui::PopStyleColor();

        ImGui::PopFont();

        ImGui::PopStyleColor();

        ImGui::EndChild();
        ImGui::End();
}
