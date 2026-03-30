#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H
#include "glad/glad.h"
#include "stb_image.h"
#include "shaderClass.h"
class Texture
{
public:
    GLuint ID;
    GLenum type;
    GLuint unit;

    Texture(const char* imagePath, GLenum texType, GLuint slot, bool ps1Mode = true);

    void TexUnit(Shader& shader, const char* uniform, GLuint slot);
    void Bind();
    void Unbind();
    void Delete();
};

#endif