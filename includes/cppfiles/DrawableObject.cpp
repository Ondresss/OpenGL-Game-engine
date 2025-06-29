#include "../headers/DrawableObject.h"

void DrawableObject::apply_transformation(const std::string& name,Transformation* transformation) const {
    this->active_program->setMat4Uniform(transformation->get_matrix(),name);
    this->active_program->setVec3(this->base_color,"color");

}
void DrawableObject::switch_transformations(const std::vector<Transformation*>& transformations) {
    this->transform_manager->register_transformations(transformations);
}

void DrawableObject::apply_material_values() {
    this->active_program->setVec3(this->model->get_material()->get_diffuse(),"material.diffuse");
    this->active_program->setVec3(this->model->get_material()->get_specular(),"material.specular");
    this->active_program->setFloat(this->model->get_material()->get_shininnes(),"material.shininess");
}


void DrawableObject::apply_texture() {
    this->active_program->setInt(this->model->get_active_texture()->get_unit(),"newTexture");
}


void DrawableObject::draw() {
    for(auto& trans : this->transform_manager->get()) {
        if(this->light_source) {
            this->light_source->shine();
        }
        this->apply_transformation("modelMatrix",trans);
        if(this->model->has_texture()) {
            this->apply_texture();
        }
        if(this->model->has_material()) {
            this->apply_material_values();
        }
        this->model->bind_VAO();
        glDrawArrays(GL_TRIANGLES,0,this->model->get_points());
    }
}