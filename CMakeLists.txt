cmake_minimum_required(VERSION 4.0.3)
project(OperationShort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_PREFIX_PATH 
    ${CMAKE_SOURCE_DIR}/vcpkg_installed/arm64-osx/include()

) 

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)


find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(${PROJECT_NAME}  
    "src/backtester.cpp"
    "src/gui.cpp"
    "src/imGuiFunction.cpp"
    "src/OperationShortApplication.cpp"
    "src/Portfolio.cpp"
    "src/Stock.cpp"
    "src/Strategy.cpp"

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
