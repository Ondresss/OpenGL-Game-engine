#version 330 core

layout(location = 0) in vec3 aPos; 

out vec3 TexCoords; 

uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix;       

void main()
{
    mat4 viewNoTranslation = mat4(mat3(viewMatrix));

    gl_Position = projectionMatrix * viewNoTranslation * vec4(aPos, 1.0);

    TexCoords = aPos; 
}
