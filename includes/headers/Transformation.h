#include"Renderer.h"
#include "TransformationComposite.h"
#pragma once
class Transformation {

private:
    glm::mat4 state;
    float current_angle;
    std::vector<TransformationComposite*> transformations;

public:
    inline Transformation(float angle) : state(glm::mat4(1.0f)),current_angle(0.0f){}
    inline Transformation() : state(glm::mat4(1.0f)),current_angle(0.0f) {};
    Transformation* rotate(float angle,const glm::vec3& axis);
    Transformation* scale(const glm::vec3& scale_dim);
    Transformation* translate(const glm::vec3& axis);    
    inline glm::mat4& get_state()  {return this->state;}
    inline void set_angle(float angle) {this->current_angle=angle;}
    inline float get_angle() const {return this->current_angle;}
    inline void add_composite(TransformationComposite* trans_composite) {this->transformations.push_back(trans_composite);}
    glm::mat4 get_matrix();
};