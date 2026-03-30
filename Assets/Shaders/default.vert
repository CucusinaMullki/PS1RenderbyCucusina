#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

uniform mat4 MVP;
uniform float snapStrength;
uniform float time;

out vec2 fragUV;

void main() {
    vec4 clipPos = MVP * vec4(position, 1.0);

    // PS1 vertex snap
    vec2 ndc = clipPos.xy / clipPos.w;
    ndc = floor(ndc * snapStrength) / snapStrength;
    clipPos.xy = ndc * clipPos.w;

    gl_Position = clipPos;
    fragUV = uv;
}