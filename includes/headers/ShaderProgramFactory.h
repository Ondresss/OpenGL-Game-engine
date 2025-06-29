#include "Renderer.h"
#include "ShaderProgram.h"
#pragma once
class ShaderProgramFactory {

private:
    ShaderProgramFactory() = delete;

public:
    static ShaderProgram* get_phong_shader();
    static ShaderProgram* get_lambert_shader();
    static ShaderProgram* get_constant_shader();
    static ShaderProgram* get_blinn_shader();
    static ShaderProgram* get_phong_texture_shader();
    static ShaderProgram* get_constant_shader_texture();
    static ShaderProgram* get_skybox_constant_shader();
};