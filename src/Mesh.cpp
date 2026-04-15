#include "Mesh.h"

void Mesh::setup()
{
    vao.Bind();

    vbo = new VBO((GLfloat*)vertices.data(), vertices.size() * sizeof(Vertex));
    ebo = new EBO(indices.data(), indices.size() * sizeof(GLuint));

    vao.LinkAttrib(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
    vao.LinkAttrib(*vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    vao.LinkAttrib(*vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    vao.UnBind();

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "Opengl error in Mesh::setup: " << err << std::endl;
    }
}

Mesh::Mesh(std::vector<Vertex> verts, std::vector<GLuint> inds, std::vector<Texture> texs) : vertices(verts), indices(inds), textures(texs)
{
    setup();
}

void Mesh::draw(Shader& shader, const glm::mat4& modelMat, const glm::mat4& view, const glm::mat4& proj)
{
    shader.Activate();

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

    for (GLuint i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i].Bind();
        glUniform1i(glGetUniformLocation(shader.ID, ("tex" + std::to_string(i)).c_str()), i);
    }

    vao.Bind();
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

    vao.UnBind();
}

void Mesh::deleteMesh()
{
    vao.Delete();
    for (auto& t : textures) t.Delete();
}