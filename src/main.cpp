#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

// Вертекс: позиция(3) + UV(2)
GLfloat vertices[] = {
//   X       Y       Z      U     V
    -0.5f,  -0.5f,  0.0f,  0.0f, 0.0f,  // нижний левый
     0.5f,  -0.5f,  0.0f,  1.0f, 0.0f,  // нижний правый
     0.0f,   0.5f,  0.0f,  0.5f, 1.0f,  // верхний
};

GLuint indices[] = {
    0, 1, 2
};

const int WIN_W = 800, WIN_H = 800;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, "PS1Render", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, WIN_W, WIN_H);
    glEnable(GL_DEPTH_TEST);

    Shader shaderProgram("Assets/Shaders/default.vert", "Assets/Shaders/default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    // layout 0 — позиция (3 float, stride = 5 float)
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    // layout 1 — UV (2 float, offset = 3 float)
    VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    VAO1.UnBind();
    VBO1.UnBind();
    EBO1.UnBind();

    // Текстура — ps1Mode=true: GL_NEAREST, без mipmap
    Texture tex("Assets/Images/Image.png", GL_TEXTURE_2D, 0, true);
    tex.TexUnit(shaderProgram, "tex0", 0);

    // PS1 uniforms
    shaderProgram.Activate();
    glUniform1f(glGetUniformLocation(shaderProgram.ID, "snapStrength"), 80.0f);
    glUniform1f(glGetUniformLocation(shaderProgram.ID, "colorDepth"),   32.0f);
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "ditherOn"),     1);

    float time = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        time += 0.016f;

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Activate();

        // Матрица вращения — демонстрирует PS1 vertex wobble
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0, 1, 0));
        glm::mat4 view  = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0), glm::vec3(0, 1, 0));
        glm::mat4 proj  = glm::perspective(glm::radians(60.0f),
                            (float)WIN_W / WIN_H, 0.1f, 100.0f);
        glm::mat4 mvp   = proj * view * model;

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "MVP"),
                           1, GL_FALSE, glm::value_ptr(mvp));
        glUniform1f(glGetUniformLocation(shaderProgram.ID, "time"), time);

        tex.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    tex.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}