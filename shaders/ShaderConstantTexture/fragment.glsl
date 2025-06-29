#version 330

in vec2 vt_out;

uniform sampler2D newTexture;

out vec4 frag_colour;

void main () {
    frag_colour = texture(newTexture, vt_out);
}

