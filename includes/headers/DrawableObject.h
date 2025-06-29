#pragma once
#include"Renderer.h"
#include"ShaderProgram.h"
#include"Model.h"
#include "TransformationManager.h"
#include "PointLight.h"
#include "BaseLight.h"
class DrawableObject {

protected:
    ShaderProgram* active_program;
    Model* model;
    TransformationManager* transform_manager;
    glm::vec3 base_color;    
    BaseLight* light_source;

public:
    inline DrawableObject() {
        this->active_program = nullptr;
        this->model = nullptr;
        this->transform_manager = new TransformationManager();
        this->base_color = glm::vec3(1.0f,1.0f,0.0f);
        this->light_source = nullptr;
    }
    inline DrawableObject(ShaderProgram* program,Model* model,const glm::vec3& color) {
        this->model = model;
        this->active_program = program;
        this->transform_manager = new TransformationManager();
        this->base_color = color;
        this->light_source = nullptr;
    }
    inline ~DrawableObject() {
        delete this->model;
        delete this->transform_manager;
        delete this->active_program;
    }
    inline void switch_program(ShaderProgram* new_program) {this->active_program = new_program;}
    inline void switch_model(Model* new_model) {this->model = new_model;}
    void switch_transformations(const std::vector<Transformation*>& transformations);
    void draw();
    inline ShaderProgram* get_active_program() {return this->active_program;}
    inline Model* get_model() {return this->model;}
    void apply_transformation(const std::string& name,Transformation* Transformation) const;
    TransformationManager* get_manager() {return this->transform_manager;}
    void set_light_source(BaseLight* light) {this->light_source = light;}
    void apply_material_values();
    void apply_texture();

};