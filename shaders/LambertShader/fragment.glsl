#version 330 core

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

out vec4 FragColorFinal;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 viewPosition;
in vec4 FragColor;
void main() {
    vec3 lightVector = normalize(lightPosition - ex_worldPosition.xyz);
    vec3 normal = normalize(ex_worldNormal);
    float diffuseFactor = max(dot(normal, lightVector), 0.0);
    vec4 diffuse = diffuseFactor * vec4(lightColor, 1.0);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    FragColorFinal = (ambient + diffuse) * FragColor;
}
