cmake_minimum_required(VERSION 3.20)
project(PS1Render)

set(CMAKE_CXX_STANDART 17)

add_executable(PS1Render
    src/main.cpp
    src/glad.c
)

target_include_directories(PS1Render PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(PS1Render PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/glfw3.lib
    opengl32
    gdi32
    dwmapi
)