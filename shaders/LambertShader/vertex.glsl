#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix; //(M-1)T
uniform vec3 color;


out vec4 FragColor;
out vec4 ex_worldPosition;
out vec3 ex_worldNormal;

void main(void){
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(aPos,1.0f);
    ex_worldPosition = modelMatrix * vec4(aPos,1.0f);
    ex_worldNormal = aNormal; 
    FragColor = vec4(color,1.0f);
}
