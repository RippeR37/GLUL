#version 330 core

in vec2 texCoords;

out vec4 color;

uniform sampler2D textureSampler;

void main() {
    //color = vec4(0.0, 1.0, 0.0, 1.0);

	color = vec4(texture(textureSampler, texCoords).rgb, 1.0);
}