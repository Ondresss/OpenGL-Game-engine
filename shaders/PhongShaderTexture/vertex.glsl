#version 330

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_texCoords;

out vec4 ex_worldPosition;
out vec3 ex_worldNormal;
out vec2 ex_texCoords;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void) {
    vec4 worldPosition = modelMatrix * vec4(in_position, 1.0);
    ex_worldPosition = worldPosition;
    ex_worldNormal = normalize(mat3(transpose(inverse(modelMatrix))) * in_normal);
    ex_texCoords = in_texCoords; 
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_position, 1.0);
}
