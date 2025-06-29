#pragma once
#include "Renderer.h"
#include "BaseLight.h"
class PointLight : public BaseLight {
private:
    glm::vec3 position;
    float shininnes;
    float constant = 1.0f;  
    float linear = 0.05f;   
    float quadratic = 0.02f;
public:
    PointLight(const glm::vec3 position,const glm::vec3 color);
    inline const glm::vec3& get_position() {return this->position;}
    inline const glm::vec3& get_color() {return this->color;}
    inline void update_position(glm::vec3 position) {this->position = position;}
    inline void update_color(glm::vec3& color) {this->color = color;}
    inline void chance_shininnes(float shininnes) {this->shininnes = shininnes;}
    inline const float get_shininnes() const {return this->shininnes;}
    void shine() override;

    inline float get_constant() const {return this->constant;}
    inline float get_linear() const {return this->linear;}
    inline float get_quadratic() const {return this->quadratic;}
};