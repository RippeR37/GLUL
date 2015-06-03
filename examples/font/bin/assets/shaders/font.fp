#version 330 core

in vec2 texCoords;

out vec4 color;

uniform sampler2D texSampler;

void main() {
    color = vec4(texture(texSampler, texCoords).r, 0.0, 0.0, 1.0);
}