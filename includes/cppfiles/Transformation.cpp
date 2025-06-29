#include "../headers/Transformation.h"

Transformation* Transformation::scale(const glm::vec3& scale_dim) {
    this->state = glm::scale(this->state,scale_dim);
    return this;
}

Transformation* Transformation::translate(const glm::vec3& axis) {
    this->state = glm::translate(this->state,axis);
    return this;
}
Transformation* Transformation::rotate(float angle,const glm::vec3& axis) {
    this->state = glm::rotate(this->state,glm::radians(angle),axis);
    return this;
}
glm::mat4 Transformation::get_matrix() {
    glm::mat4 matrix = glm::mat4(1.0f);
    for(auto& trans : this->transformations) {
        if(!trans) {
            printf("Invalid transformation\n");
            exit(EXIT_FAILURE);
        }
        matrix = matrix * trans->get_matrix();
    }
    return matrix;
}