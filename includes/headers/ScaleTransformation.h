#include "TransformationBase.h"
#pragma once
class ScaleTransformation : public TransformationBase {

public:
    inline ScaleTransformation(const glm::vec3& factor) : TransformationBase() {
        this->matrix = glm::scale(this->matrix,factor);
    }
    const glm::mat4& get_matrix() override {return this->matrix;}
};