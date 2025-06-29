#include "TransformationBase.h"
#pragma once
class RotationTransformation : public TransformationBase {

public:
    RotationTransformation(float angle,const glm::vec3& axis) : TransformationBase() {
        this->matrix = glm::rotate(this->matrix,glm::radians(angle),axis);
    }
    const glm::mat4& get_matrix() override {return this->matrix;}
};