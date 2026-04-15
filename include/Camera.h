#ifndef CAMERA_H
#define CAMERA_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "Transform3D.h"
#include "shaderClass.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm/gtx/string_cast.hpp"

class Camera : public Transform3D
{
    float fov;
    float nearPlane, farPlane;
    int screenW, screenH;
    float sensitivity = 0.1f;
    float speed = 5.0f;

    bool ps1SnapCamera = true;
    float snapGrid = 0.05f;

    glm::mat4 viewMatrix;
    glm::mat4 projMatrix;

    bool firstClick = true;
    float lastX = 0, lastY = 0;

    void updateMatrices();
public:
    Camera(int w, int h, glm::vec3 startPos, float fovDeg, float nearP, float farP);

    void update(GLFWwindow* window, float deltaTime);
    void sendToShader(Shader& shader);

    glm::mat4 GetViewMatrix() { return viewMatrix; }
    glm::mat4 GetProjMatrix() { return projMatrix; }

    void handleKeybourde(GLFWwindow* window, float deltaTime);

    void handleMouse(GLFWwindow* window);
};
#endif