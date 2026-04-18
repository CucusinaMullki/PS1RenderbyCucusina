#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Light.h"
#include <string>

class PointLight : public Light 
{
    public: 
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    PointLight() = default;
    PointLight(glm::vec3 pos, glm::vec3 col, float intens, float lin = 0.09f, float quad = 0.032f) : Light(col, intens), linear(lin), quadratic(quad)
    {
        position = pos;
    }

    void sendToShader(Shader& shader, int index) override;
};

#endif 