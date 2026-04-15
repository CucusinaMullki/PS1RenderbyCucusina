#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

class Transform3D
{
public:

    glm::vec3 GetPosition() { return position; }
    glm::vec3 GetRotation() { return rotation; }
    glm::vec3 GetScale() { return scale; }

    glm::vec3 GetForwardVector() { return forward; }
    glm::vec3 GetRightVector() { return right; }
    glm::vec3 GetUpVector() { return up; }

    void SetPosition(glm::vec3 pos);
    void SetRotation(float pitch, float yaw, float roll);
    void SetScale(glm::vec3 s);
    void Translate(glm::vec3 delta);
    void Rotate(float pitch, float yaw, float roll);

    void MoveForward(float dist);
    void MoveRight(float dist);
    void MoveUp(float dist);

    const glm::mat4& getMatrix() const { return modelMatrix; }

protected:
    void rebuildAxes();
    void rebuildMatrix();
    
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);

    glm::vec3 forward = glm::vec3(0, 0, -1);
    glm::vec3 right = glm::vec3(1, 0, 0);
    glm::vec3 up = glm::vec3(0, 0, 1);

    glm::mat4 modelMatrix = glm::mat4(1.0f);

};

#endif 