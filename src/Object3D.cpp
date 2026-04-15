#include "Object3D.h"

void Object3D::draw(Shader& shader, const glm::mat4& view, const glm::mat4& proj)
{
    if (!visible) return;
    for (auto& mesh : meshes)
        mesh.draw(shader, getMatrix(), view, proj);
}

void Object3D::deleteObject()
{
    for (auto& m : meshes) m.deleteMesh();
}