#include "Renderer.h"
#pragma once
class TransformationBase {
protected:
    glm::mat4 matrix;
public:
    inline TransformationBase() : matrix(glm::mat4(1.0f)) {}
    virtual const glm::mat4& get_matrix() = 0;
};