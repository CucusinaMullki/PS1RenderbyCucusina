#include "Camera.h"

Camera::Camera(int w, int h, glm::vec3 startPos,
               float fovDeg, float nearP, float farP)
    : screenW(w), screenH(h), fov(fovDeg),
      nearPlane(nearP), farPlane(farP)
{
    position = startPos;
    rebuildAxes();
    updateMatrices();
}

void Camera::update(GLFWwindow* window, float deltaTime) {
    handleKeybourde(window, deltaTime);
    handleMouse(window);
    updateMatrices();
}

void Camera::sendToShader(Shader& shader) {
    
    shader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"),
                       1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "proj"),
                       1, GL_FALSE, glm::value_ptr(projMatrix));
    glUniform3fv      (glGetUniformLocation(shader.ID, "camPos"),
                       1, glm::value_ptr(position));
}

void Camera::updateMatrices() {
    glm::vec3 pos = position;
    if (ps1SnapCamera)
        pos = glm::round(pos / snapGrid) * snapGrid;

    viewMatrix = glm::lookAt(pos, pos + forward, up);
    projMatrix = glm::perspective(
        glm::radians(fov), (float)screenW / screenH,
        nearPlane, farPlane
    );

    std::cout << "View Matrix: " << glm::to_string(viewMatrix) << std::endl;
    std::cout << "Proj Matrix: " << glm::to_string(projMatrix) << std::endl;
}

void Camera::handleKeybourde(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) MoveForward( speed * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) MoveForward(-speed * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) MoveRight  ( speed * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) MoveRight  (-speed * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) MoveUp     ( speed * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) MoveUp     (-speed * deltaTime);
}

void Camera::handleMouse(GLFWwindow* window) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        double mx, my;
        glfwGetCursorPos(window, &mx, &my);

        if (firstClick) {
            lastX = (float)mx;
            lastY = (float)my;
            firstClick = false;
        }

        float dx = ((float)mx - lastX) * sensitivity;
        float dy = ((float)my - lastY) * sensitivity;
        lastX = (float)mx;
        lastY = (float)my;

        rotation.y += glm::radians(dx);
        rotation.x -= glm::radians(dy);
        rotation.x  = glm::clamp(rotation.x,
                        glm::radians(-89.0f),
                        glm::radians( 89.0f));
        rebuildAxes();
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}