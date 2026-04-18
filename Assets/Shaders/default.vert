#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform float snapStrength;

out vec2 fragUV;
out vec3 fragNormal;
out vec3 fragPos;      // ← добавить

void main() {
    vec4 worldPos = model * vec4(position, 1.0);
    fragPos    = worldPos.xyz;   // ← мировая позиция фрагмента

    vec4 clipPos = proj * view * worldPos;

    // PS1 snap
    vec2 ndc = clipPos.xy / clipPos.w;
    ndc = floor(ndc * snapStrength) / snapStrength;
    clipPos.xy = ndc * clipPos.w;

    gl_Position = clipPos;
    fragUV      = uv;
    fragNormal  = mat3(transpose(inverse(model))) * normal;
}