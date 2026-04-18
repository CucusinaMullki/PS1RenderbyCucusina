#version 330 core

#define MAX_POINT_LIGHTS 4
#define MAX_SPOT_LIGHTS  2

// Структуры
struct PointLightData {
    vec3  position;
    vec3  color;
    float intensity;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLightData {
    vec3  position;
    vec3  direction;
    vec3  color;
    float intensity;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};

uniform sampler2D     tex0;
uniform float         colorDepth;
uniform int           ditherOn;
uniform int           numPointLights;
uniform int           numSpotLights;
uniform vec3          camPos;
uniform PointLightData pointLights[MAX_POINT_LIGHTS];
uniform SpotLightData  spotLights[MAX_SPOT_LIGHTS];

in vec2 fragUV;
in vec3 fragNormal;
in vec3 fragPos;
out vec4 fragColor;

// Матрица Байера
float bayer[16] = float[](
     0.0/16.0,  8.0/16.0,  2.0/16.0, 10.0/16.0,
    12.0/16.0,  4.0/16.0, 14.0/16.0,  6.0/16.0,
     3.0/16.0, 11.0/16.0,  1.0/16.0,  9.0/16.0,
    15.0/16.0,  7.0/16.0, 13.0/16.0,  5.0/16.0
);

// Затухание по расстоянию
float attenuation(float dist, float c, float l, float q) {
    return 1.0 / (c + l * dist + q * dist * dist);
}

// PS1: квантуем освещение до 8 уровней
float quantizeLight(float v) {
    return floor(v * 8.0) / 8.0;
}

vec3 calcPointLight(PointLightData light, vec3 normal, vec3 fragP) {
    vec3  lightDir = normalize(light.position - fragP);
    float dist     = length(light.position - fragP);
    float att      = attenuation(dist, light.constant, light.linear, light.quadratic);
    float diff     = quantizeLight(max(dot(normal, lightDir), 0.0));
    return light.color * light.intensity * diff * att;
}

vec3 calcSpotLight(SpotLightData light, vec3 normal, vec3 fragP) {
    vec3  lightDir = normalize(light.position - fragP);
    float dist     = length(light.position - fragP);
    float att      = attenuation(dist, light.constant, light.linear, light.quadratic);

    // Конус — плавное затухание на границе
    float theta   = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float spotF   = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    float diff = quantizeLight(max(dot(normal, lightDir), 0.0));
    return light.color * light.intensity * diff * att * spotF;
}

void main() {
    vec3 texColor = texture(tex0, fragUV).rgb;
    vec3 normal   = normalize(fragNormal);

    // Ambient — базовый PS1 уровень освещения
    vec3 ambient = vec3(0.15);
    vec3 lighting = ambient;

    for (int i = 0; i < numPointLights; i++)
        lighting += calcPointLight(pointLights[i], normal, fragPos);

    for (int i = 0; i < numSpotLights; i++)
        lighting += calcSpotLight(spotLights[i], normal, fragPos);

    vec3 result = texColor * lighting;

    // Дизеринг
    if (ditherOn == 1) {
        int x = int(mod(gl_FragCoord.x, 4.0));
        int y = int(mod(gl_FragCoord.y, 4.0));
        result += (bayer[y * 4 + x] - 0.5) / colorDepth;
    }

    // Квантование цвета
    result = floor(result * colorDepth) / colorDepth;

    fragColor = vec4(result, 1.0);
}