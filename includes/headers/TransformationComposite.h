#include "TransformationBase.h"
#include <vector>
#pragma once

class TransformationComposite : TransformationBase {

private:
    std::vector<TransformationBase*> transformations;
    glm::mat4 out;
public:
    inline TransformationComposite() : TransformationBase(), out(glm::mat4(1.0f)) {}
    const glm::mat4& get_matrix() override;
    TransformationComposite* add(TransformationBase* trans);

};