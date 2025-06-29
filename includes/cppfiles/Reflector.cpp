#include "../headers/Reflector.h"

void Reflector::shine() {
    this->reflecting = !this->reflecting;
    this->notify();
}

float Reflector::calculate_inner_cutoff() const {
    return std::cos(glm::radians(this->inner_angle));
}
float Reflector::calculate_outer_cutoff() const {
    return std::cos(glm::radians(this->outer_angle));
}