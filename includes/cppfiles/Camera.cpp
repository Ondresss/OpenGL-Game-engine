#include "../headers/Camera.h"
#include "../headers/ShaderProgram.h"
void Camera::move_back() {
    this->movement -=  glm::normalize(this->mouse->get_direction()) * this->speed;
}
void Camera::move_forward() {
    this->movement += glm::normalize(this->mouse->get_direction()) * this->speed;
}
void Camera::move_left() {
    glm::vec3 right_vec = glm::normalize(glm::cross(this->mouse->get_direction(),this->up));
    this->movement -= right_vec * this->speed;
}
void Camera::move_right() {
    glm::vec3 right_vec = glm::normalize(glm::cross(this->mouse->get_direction(),this->up));
    this->movement += right_vec * this->speed;
}
void Camera::move() {
    this->position+=this->movement;
    this->reflector->update_position(this->position);
    this->reflector->update_direction(glm::normalize(this->mouse->get_direction()));
    this->notify();
}

void Camera::register_reflector_observers(ShaderProgram* program) {
    this->reflector->add(program);
    program->addSubject(this->reflector);
    
}