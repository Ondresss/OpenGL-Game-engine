#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 Color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 fragColor;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Color = vec4(fragColor,1.0f);  
}