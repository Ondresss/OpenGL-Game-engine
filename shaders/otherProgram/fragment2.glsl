#version 330 core

out vec4 FragColor;
uniform vec3 vertexColor;
in vec2 TextCoord;
uniform sampler2D uTexture;
uniform vec3 sourceColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;  

in vec3 Normal;
in vec3 FragPos;

void main() {
    vec3 ambient = light.ambient *  vec3(texture(material.diffuse, TextCoord));
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse *  diff * vec3(texture(material.diffuse,TextCoord));

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = ( material.specular * spec) * light.specular;  

    vec3 result = ambient + diffuse + specular; 
    FragColor = vec4(result, 1.0);
    
}