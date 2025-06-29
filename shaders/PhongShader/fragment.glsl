#version 330
#define MAX_LIGHTS 40

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec4 v_Color;   
out vec4 FragColorFinal;

struct Light {
    int type;
    vec3 position;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
    vec3 direction;
    float innerCutoff;
    float outerCutoff;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform vec3 viewPosition;
uniform int no_lights;
uniform Light lights[MAX_LIGHTS]; 
uniform Material material;

void main(void) {
    vec3 convertedWorldPos = ex_worldPosition.xyz / ex_worldPosition.w;
    vec3 normal = normalize(ex_worldNormal);
    vec3 viewDir = normalize(viewPosition - convertedWorldPos);

    vec4 ambient = vec4(material.ambient,1.0f) * vec4(material.diffuse, 1.0);
    vec4 diffuse = vec4(0.0);
    vec4 specular = vec4(0.0);

    for(int i = 0; i < no_lights; i++) {
        if (lights[i].type == 1) {
            vec3 lightDir = lights[i].position - convertedWorldPos;
            float distance = length(lightDir);
            lightDir = normalize(lightDir);

            float attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));

            float diffuseFactor = max(dot(normal, lightDir), 0.0);
            if (diffuseFactor > 0.0) {
                diffuse += attenuation * diffuseFactor * v_Color  * vec4(material.diffuse * lights[i].color, 1.0);

                vec3 reflectDir = reflect(-lightDir, normal);
                float specFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); 
                specular += attenuation * specFactor * v_Color * vec4(material.specular * lights[i].color, 1.0);
            }
        }

        if (lights[i].type == 2) {
            vec3 lightDir = lights[i].position - convertedWorldPos;
            float distance = length(lightDir);
            lightDir = normalize(lightDir);

            float attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));

            float angle = dot(lightDir, normalize(-lights[i].direction));
            float alpha = max(lights[i].innerCutoff - lights[i].outerCutoff, 0.001);
            float intensity = clamp((angle - lights[i].outerCutoff) / alpha, 0.0, 1.0);
            float diffuseFactor = max(dot(normal, lightDir), 0.0);
            if (diffuseFactor > 0.0) {
                diffuse += intensity * attenuation * diffuseFactor * v_Color * vec4(material.diffuse * lights[i].color, 1.0);

                vec3 reflectDir = reflect(-lightDir, normal);
                float specFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); 
                specular += intensity *  attenuation * specFactor * v_Color * vec4(material.specular * lights[i].color, 1.0);
            }
        }
        if (lights[i].type == 3) {
            vec3 lightDir = normalize(-lights[i].direction);

            float diffuseFactor = max(dot(normal, lightDir), 0.0);
                diffuse += diffuseFactor * v_Color * vec4(material.diffuse * lights[i].color, 1.0);

                vec3 reflectDir = reflect(-lightDir, normal);
                float specFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); 
                specular += specFactor * v_Color * vec4(material.specular * lights[i].color, 1.0);
        }
    }

    FragColorFinal = ambient + diffuse + specular;

    if (no_lights == 0) {
        FragColorFinal = ambient;
    }
}
