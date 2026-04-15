#include "Transform3D.h"

void Transform3D::rebuildMatrix()
{
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0, 0, 1));
    modelMatrix = glm::scale(modelMatrix, scale);
}

void Transform3D::rebuildAxes()
{
    float pitch = rotation.x;
    float yaw = rotation.y;

    forward.x = cos(yaw) * cos(pitch);
    forward.y = sin(pitch);
    forward.z = sin(yaw) * cos(pitch);
    forward = glm::normalize(forward);

    right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
    up = glm::normalize(glm::cross(right, forward));
}

void Transform3D::SetPosition(glm::vec3 pos)
{
    position = pos;
    rebuildMatrix();
}

void Transform3D::SetRotation(float pitch, float yaw, float roll)
{
    rotation = glm::vec3(pitch, yaw, roll);
    rebuildAxes();
    rebuildMatrix();
}

void Transform3D::SetScale(glm::vec3 s)
{
    scale = s;
    rebuildMatrix();
}

void Transform3D::Translate(glm::vec3 delta)
{
    position += delta;
    rebuildMatrix();
}

void Transform3D::Rotate(float pitch, float yaw, float roll)
{
    rotation += glm::vec3(pitch, yaw, roll);
    rebuildAxes();
    rebuildMatrix();
}

void Transform3D::MoveForward(float dist) { position += forward * dist; rebuildMatrix(); }
void Transform3D::MoveRight(float dist) { position += right * dist; rebuildMatrix(); }
void Transform3D::MoveUp(float dist) { position += up * dist; rebuildMatrix(); }