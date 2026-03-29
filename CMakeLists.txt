cmake_minimum_required(VERSION 3.20)
project(PS1Render)

set(CMAKE_CXX_STANDARD 17)

add_executable(PS1Render
    src/main.cpp
    src/glad.c
    src/VAO.cpp
    src/VBO.cpp
    src/EBO.cpp
    src/shaderClass.cpp
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

add_custom_command(TARGET PS1Render POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Assets
    $<TARGET_FILE_DIR:PS1Render>/Assets
)