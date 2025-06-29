#include "Renderer.h"
#include "BaseLight.h"
#include <cmath>
#pragma once
class Reflector : public BaseLight {

private:
    glm::vec3 position;
    glm::vec3 direction;
    float constant = 1.0f;  
    float linear = 0.05f;   
    float quadratic = 0.02f;
    bool reflecting;
    float inner_angle;
    float outer_angle;
public:

    inline Reflector() : BaseLight(glm::vec3(1.0f,1.0f,1.0f)),position(glm::vec3(0.0f)),direction(glm::vec3(0.0f,0.0f,1.0f)),reflecting(false),inner_angle(10.0f),outer_angle(45.0f) {} 

    void shine() override;

    inline void  update_position(const glm::vec3& pos) {this->position = pos;}
    inline void  update_direction(const glm::vec3& dir) {this->direction = dir;}
    inline const glm::vec3& get_position() const {return this->position;}
    inline const glm::vec3& get_direction() const {return this->direction;}
    inline float get_constant() const {return this->constant;}
    inline float get_linear() const {return this->linear;}
    inline float get_quadratic() const {return this->quadratic;}
    inline bool  is_reflecting() {return this->reflecting;}

    float calculate_inner_cutoff() const;
    float calculate_outer_cutoff() const;
};