#version 330 core

in vec2 texCoords;

out vec4 color;

uniform sampler2D glyphAtlas;

uniform vec4 fontColor;

void main() {
    color = vec4(fontColor.rgb, fontColor.a * texture(glyphAtlas, texCoords).r);
}