#ifndef OBJECT3D_H
#define OBJECT3D_H
#include "vector"
#include "Transform3D.h"
#include "Mesh.h"
#include "shaderClass.h"

class Object3D : public Transform3D {
    std::vector<Mesh> meshes;
    std::string name;
    bool visible = true;
public:
    Object3D() = default;
    Object3D::Object3D(std::vector<Mesh> meshes, std::string name)
    : meshes(meshes), name(name), visible(true) {}

    void draw(Shader& shader, const glm::mat4& view, const glm::mat4& proj);
    void deleteObject();
};

#endif