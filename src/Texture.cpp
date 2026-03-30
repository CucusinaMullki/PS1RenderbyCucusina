#include "Texture.h"
#include "iostream"

Texture::Texture(const char* imagePath, GLenum texType, GLuint slot, bool ps1Mode)
{
    type = texType;
    unit = slot;

    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;
    unsigned char* data = stbi_load(imagePath, &width, &height, &channels, 0);
    if (!data)
    {
        std::cerr << "TEXTURE ERROR: Cannot load " << imagePath << "\n"
                  << stbi_failure_reason() << "\n";

        unsigned char pink[] = {255, 0, 255, 255};
        data = pink;
        width = height = 1;
        channels = 4;
    }

    GLenum internalFormat, dataFormat;

    switch(channels)
    {
        case 4: internalFormat = GL_RGBA8; dataFormat = GL_RGBA; break;
        case 3: internalFormat = GL_RGB8; dataFormat = GL_RGB; break;
        case 1: internalFormat = GL_R8; dataFormat = GL_RED; break;
        default: internalFormat = GL_RGB8; dataFormat = GL_RGB ; break; 
    }

    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(type, ID);

    if(ps1Mode)
    {
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else
    {
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    glTexImage2D(type, 0, internalFormat, width, height, 0,
                 dataFormat, GL_UNSIGNED_BYTE, data);

    if (!ps1Mode)
        glGenerateMipmap(type);

    stbi_image_free(data);
    glBindTexture(type, 0);
}

void Texture::TexUnit(Shader& shader, const char* uniform, unsigned int unit)
{
    // Активируем шейдер
    shader.Activate();
    // Устанавливаем юнит текстуры
    glUniform1i(glGetUniformLocation(shader.ID, uniform), unit);
    // Привязываем текстуру к указанному юниту
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(type, ID);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(type, ID);
}

void Texture::Unbind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}