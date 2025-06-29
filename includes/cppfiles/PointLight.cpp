#include "../headers/PointLight.h"
#include "../headers/DrawableObject.h"

PointLight::PointLight(glm::vec3 position,glm::vec3 color) : BaseLight(color),position(position),shininnes(10) {}

void PointLight::shine() {
    this->notify();
}

