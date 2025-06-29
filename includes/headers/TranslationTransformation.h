#include "TransformationBase.h"
#pragma once
class TranslationTransformation : public TransformationBase {

public:
    TranslationTransformation(const glm::vec3& trans_vector) : TransformationBase() {
        this->matrix = glm::translate(this->matrix,trans_vector);
    }


    const glm::mat4& get_matrix() override {return this->matrix;}
};