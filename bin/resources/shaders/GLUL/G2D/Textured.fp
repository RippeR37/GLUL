#version 330 core

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 finalColor;

uniform sampler2D texSampler;


void main() {
    finalColor = fragmentColor * texture(texSampler, fragmentUV);
}
