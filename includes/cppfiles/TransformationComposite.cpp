#include "../headers/TransformationComposite.h"

const glm::mat4& TransformationComposite::get_matrix() {
    this->out = glm::mat4(1.0f);
    for(auto& tran : this->transformations) {
        this->out = this->out * tran->get_matrix();
    }
    return this->out;
}
TransformationComposite* TransformationComposite::add(TransformationBase* base) {
    this->transformations.push_back(base);
    return this;

}