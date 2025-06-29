#version 330
#define MAX_LIGHTS 40

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 ex_texCoords;
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

uniform sampler2D newTexture; 
uniform vec3 viewPosition;
uniform int no_lights;
uniform Light lights[MAX_LIGHTS]; 

void main(void) {
    vec3 convertedWorldPos = ex_worldPosition.xyz / ex_worldPosition.w;
    vec3 normal = normalize(ex_worldNormal);
    vec3 viewDir = normalize(viewPosition - convertedWorldPos);

    vec2 convertedTexCoords = ex_texCoords * 20;
    vec4 texColor = texture(newTexture, convertedTexCoords); 

   
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * texColor; 
    vec4 diffuse = vec4(0.0);
    vec4 specular = vec4(0.0);

    for (int i = 0; i < no_lights; i++) {
        if (lights[i].type == 1) { 
            vec3 lightDir = lights[i].position - convertedWorldPos;
            float distance = length(lightDir);
            lightDir = normalize(lightDir);

            float attenuation = 1.0 / (0.1 + 0.01 * distance + 0.001 * distance * distance); 
            float diffuseFactor = max(dot(normal, lightDir), 0.0);
 
           if (diffuseFactor > 0.0) {
                diffuse += attenuation * diffuseFactor * texColor;

                vec3 reflectDir = reflect(-lightDir, normal);
                float specFactor = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); 
                specular += attenuation * specFactor * vec4(lights[i].color, 1.0);
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
                diffuse += intensity * attenuation * diffuseFactor * texColor * vec4(lights[i].color, 1.0);

                vec3 reflectDir = reflect(-lightDir, normal);
                float specFactor = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); 
                specular += intensity * attenuation * specFactor * vec4(lights[i].color, 1.0);
            }
        }

        if (lights[i].type == 3) { 
            vec3 lightDir = normalize(-lights[i].direction);
            float diffuseFactor = max(dot(normal, lightDir), 0.0);

            diffuse += diffuseFactor * texColor * vec4(lights[i].color, 1.0);

            vec3 reflectDir = reflect(-lightDir, normal);
            float specFactor = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); 
            specular += specFactor * vec4(lights[i].color, 1.0);
        }
    }

    FragColorFinal = clamp(ambient + diffuse + specular, 0.0, 1.0); 

    if (no_lights == 0) {
        FragColorFinal = ambient;
    }
}
