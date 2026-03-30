#version 330 core

uniform sampler2D tex0;
uniform float colorDepth;
uniform int ditherOn;

in vec2 fragUV;
out vec4 fragColor;

float bayer[16] = float[](
     0.0/16.0,  8.0/16.0,  2.0/16.0, 10.0/16.0,
    12.0/16.0,  4.0/16.0, 14.0/16.0,  6.0/16.0,
     3.0/16.0, 11.0/16.0,  1.0/16.0,  9.0/16.0,
    15.0/16.0,  7.0/16.0, 13.0/16.0,  5.0/16.0
);

void main() {
    vec3 color = texture(tex0, fragUV).rgb;

    if (ditherOn == 1) {
        int x = int(mod(gl_FragCoord.x, 4.0));
        int y = int(mod(gl_FragCoord.y, 4.0));
        color += (bayer[y * 4 + x] - 0.5) / colorDepth;
    }

    // Квантование цвета — 32 уровня как на PS1
    color = floor(color * colorDepth) / colorDepth;

    fragColor = vec4(color, 1.0);
}