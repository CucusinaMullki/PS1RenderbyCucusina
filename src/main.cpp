#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaderClass.h"
#include "Camera.h"
#include "Object3D.h"
#include "ModelLoader.h"

const int W = 800, H = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(W, H, "PS1", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glEnable(GL_DEPTH_TEST);

    Shader shader("Assets/Shaders/default.vert",
                  "Assets/Shaders/default.frag");

    // PS1 uniforms
    shader.Activate();
    glUniform1f(glGetUniformLocation(shader.ID, "snapStrength"), 80.0f);
    glUniform1f(glGetUniformLocation(shader.ID, "colorDepth"),   32.0f);
    glUniform1i(glGetUniformLocation(shader.ID, "ditherOn"),     1);

    Camera camera(W, H, glm::vec3(0, 1, 3), 60.0f, 0.1f, 100.0f);

    // Загрузка модели
    Object3D obj(
        ModelLoader::load("Assets/Model/Coin.obj", "Assets/Model",
                          "Assets/Images/Coin_DefaultMaterial_BaseColor.png"),
        "crate"
    );
    obj.SetPosition({0, 0, -3}); 
    obj.SetScale({1, 1, 1});

    float lastTime = 0;

    while (!glfwWindowShouldClose(window)) {
        float now  = (float)glfwGetTime();
        float dt   = now - lastTime;
        lastTime   = now;

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.update(window, dt);
        camera.sendToShader(shader);

        // Медленное вращение объекта
        obj.Rotate(0, 0.5f * dt, 0);
        obj.draw(shader, camera.GetViewMatrix(), camera.GetProjMatrix());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    obj.deleteObject();
    shader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}