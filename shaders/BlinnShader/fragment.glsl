#version 330 core

in vec4 FragColor;
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

out vec4 color;

uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 lightColor;
uniform float shininnes;

void main() {
    vec3 norm = normalize(ex_worldNormal);
    vec3 lightDir = normalize(lightPosition - vec3(ex_worldPosition));
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    vec3 viewDir = normalize(viewPosition - vec3(ex_worldPosition));
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), shininnes);
    vec3 specular = spec * lightColor;
    
    vec3 ambient = 0.1 * lightColor;
    vec3 lighting = ambient + diffuse + specular;

    color = vec4(lighting * vec3(FragColor), 1.0);
}
