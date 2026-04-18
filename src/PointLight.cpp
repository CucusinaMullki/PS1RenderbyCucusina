#include "PointLight.h"

void PointLight::sendToShader(Shader& shader, int index) {
    shader.Activate();
     std::string base = "pointLights[" + std::to_string(index) + "].";
     glUniform3fv(glGetUniformLocation(shader.ID, (base + "position").c_str()),
                  1, glm::value_ptr(position));
     glUniform3fv(glGetUniformLocation(shader.ID, (base + "color").c_str()),
                  1, glm::value_ptr(color));
     glUniform1f(glGetUniformLocation(shader.ID, (base + "intensity").c_str()),
                 intensity);
     glUniform1f(glGetUniformLocation(shader.ID, (base + "constant").c_str()),
                 constant);
     glUniform1f(glGetUniformLocation(shader.ID, (base + "linear").c_str()),
                 linear);
     glUniform1f(glGetUniformLocation(shader.ID, (base + "quadratic").c_str()),
                 quadratic);
}