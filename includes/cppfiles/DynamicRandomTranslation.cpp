#include "../headers/DynamicRandomTranslation.h"

const glm::mat4& DynamicRandomTranslation::get_matrix() {
    return glm::translate(this->matrix,this->movement);
}