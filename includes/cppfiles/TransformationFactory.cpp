#include "../headers/TransformationFactory.h"

Transformation* TransformationFactory::get_transformation() {
    return (new Transformation())->scale(glm::vec3(0.3f,0.3f,0.3f));
}