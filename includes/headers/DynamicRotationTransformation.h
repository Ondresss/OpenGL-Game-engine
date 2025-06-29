#include "Renderer.h"
#include "TransformationBase.h"

#pragma once

class DynamicRotationTransformation : public TransformationBase {

private:
    float current_angle;
    glm::vec3 rotation_axis;
public:
    DynamicRotationTransformation(float start_angle,glm::vec3 rotation_axis) : TransformationBase() {
        this->current_angle = start_angle;
        this->rotation_axis = rotation_axis;
    }

    const glm::mat4& get_matrix() override;


};