#include "../headers/DynamicRotationTransformation.h"

const glm::mat4& DynamicRotationTransformation::get_matrix() {
    this->matrix = glm::mat4(1.0f); 
    
    this->current_angle += 1.0f; 
    float radians = glm::radians(this->current_angle);
    
    this->matrix = glm::rotate(this->matrix, radians, this->rotation_axis);
    
    return this->matrix;
}