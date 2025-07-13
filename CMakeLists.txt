cmake_minimum_required(VERSION 4.0.3)
project(OperationShort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH 
    ${CMAKE_SOURCE_DIR}/vcpkg_installed/arm64-osx/include()

) 

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/imgui)


find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(${PROJECT_NAME}  
    "src/gui.cpp"
    "src/backtester.hpp"
    "src/backtester.cpp"
    # src/imgui/imgui_impl_glfw.cpp
    # src/imgui/imgui_impl_opengl3.cpp
    "src/imGuiFunction.cpp"
    "src/backtester.cpp"
    "src/OperationShortApplication.cpp"
    "src/Portfolio.cpp"
    "src/Strategy.cpp"
    "src/UsingImGui.h"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        glfw
        glad::glad
        imgui::imgui
)


if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()
