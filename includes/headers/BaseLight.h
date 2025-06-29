#include "Renderer.h"
#include "Subject.h"
#pragma once
class BaseLight : public Subject {
protected:
    glm::vec3 color;
public:
    inline BaseLight(glm::vec3 color) : Subject(),color(color) {}
    virtual void shine() = 0;
    inline const glm::vec3& get_color() {return this->color;}
};