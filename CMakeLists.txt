cmake_minimum_required(VERSION 3.21)  # 3.21+ recommended for vcpkg + JSON better support
project(OperationShort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_PREFIX_PATH 
    ${CMAKE_SOURCE_DIR}/vcpkg_installed/arm64-osx/include
) 

# Include your own project headers
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Find libraries via vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)  # NEW

# Your executable
add_executable(${PROJECT_NAME}
    "src/backtester.cpp"
    "src/gui.cpp"
    "src/imGuiFunction.cpp"
    "src/Portfolio.cpp"
    "src/Stock.cpp"
    "src/Strategy.cpp"
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw
        glad::glad
        imgui::imgui
        ${Python3_LIBRARIES}           # NEW
)

# Include Python headers
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${Python3_INCLUDE_DIRS}        # NEW
)

# macOS-specific system frameworks
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()
