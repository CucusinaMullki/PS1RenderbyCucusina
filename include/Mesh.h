#ifndef MESH_H
#define MESH_H
#include "vector"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "shaderClass.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
};

class Mesh
{
    VBO* vbo = nullptr;
    EBO* ebo = nullptr;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    void setup();
    public:

    VAO vao;
    Mesh(std::vector<Vertex> verts, std::vector<GLuint> ind, std::vector<Texture> texs);

    void draw(Shader& shader, const glm::mat4& modelMat, const glm::mat4& view, const glm::mat4& proj);

    void deleteMesh();
};

#endif 
