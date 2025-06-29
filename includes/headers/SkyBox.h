#include "Renderer.h"
#include "Texture.h"
#include "Cube.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "ShaderProgramFactory.h"
#include "SkyBoxModel.h"
#include <vector>
#pragma once
class SkyBox : public Texture {
private:
    Model* model;
    ShaderProgram* program;
public:
    SkyBox(const std::vector<std::string>& faces);
    inline ~SkyBox() {
        delete this->model;
        delete this->program;
    }
    int load(const std::vector<std::string>& faces);
    inline void set_skybox_shaderProgram(ShaderProgram* program) {this->program = program;}
    inline Model* get_model() const {return this->model;}
    inline bool has_program() {nullptr != this->program;}
    inline ShaderProgram* get_program()  { return this->program; }

    void bindAll();

};
