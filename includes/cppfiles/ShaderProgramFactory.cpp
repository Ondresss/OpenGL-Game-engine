#include "../headers/ShaderProgramFactory.h"
ShaderProgram* ShaderProgramFactory::get_blinn_shader() {
    return new ShaderProgram("./shaders/BlinnShader/vertex.glsl","./shaders/BlinnShader/fragment.glsl");
}
ShaderProgram* ShaderProgramFactory::get_lambert_shader() {
    return new ShaderProgram("./shaders/LambertShader/vertex.glsl","./shaders/LambertShader/fragment.glsl");
}

ShaderProgram* ShaderProgramFactory::get_phong_shader() {
    return new ShaderProgram("./shaders/PhongShader/vertex.glsl","./shaders/PhongShader/fragment.glsl");
}

ShaderProgram* ShaderProgramFactory::get_constant_shader() {
    return new ShaderProgram("./shaders/ShaderProgram1/vertex.glsl","./shaders/ShaderProgram1/fragment.glsl");
}
ShaderProgram* ShaderProgramFactory::get_phong_texture_shader() {
    return new ShaderProgram("./shaders/PhongShaderTexture/vertex.glsl","./shaders/PhongShaderTexture/fragment.glsl");
}
ShaderProgram* ShaderProgramFactory::get_constant_shader_texture() {
    return new ShaderProgram("./shaders/ShaderConstantTexture/vertex.glsl","./shaders/ShaderConstantTexture/fragment.glsl");
}
ShaderProgram* ShaderProgramFactory::get_skybox_constant_shader() {
    return new ShaderProgram("./shaders/SkyBoxShader/vertex.glsl","./shaders/SkyBoxShader/fragment.glsl");
}
