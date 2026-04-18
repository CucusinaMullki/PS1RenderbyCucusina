#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm/glm.hpp>
#include "glm/glm/gtc/type_ptr.hpp"
#include "Transform3D.h"
#include "shaderClass.h"

class Light : public Transform3D
{
public:
    glm::vec3 color = glm::vec3(1.0f);
    float intensity = 1.0f;

    Light() = default;
    Light(glm::vec3 col, float intens) : color(col), intensity(intens) {}

    virtual void sendToShader(Shader& shader, int index) = 0;
    virtual ~Light() = default;
};

#endif