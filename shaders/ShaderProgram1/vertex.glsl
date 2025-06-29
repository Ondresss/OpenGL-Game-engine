#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
out vec4 Color;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projectionMatrix;
uniform vec3 color;


void main() {
    Color = vec4(color,1.0f);
    gl_Position = projectionMatrix *  viewMatrix *  modelMatrix *  vec4(aPos,1.0f);

}