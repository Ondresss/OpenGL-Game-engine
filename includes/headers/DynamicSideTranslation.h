#include "Renderer.h"
#include "TransformationBase.h"
#include <utility>


class DynamicSideTranslation : public TransformationBase {
private:
    glm::vec3 pointA;
    glm::vec3 pointB;

    glm::vec3 direction;
    float speed;
public:
    inline DynamicSideTranslation(glm::vec3 A,glm::vec3 B,float speed) : TransformationBase() {
        this->pointA = A;
        this->pointB = B;
        this->speed = speed;
        this->direction = glm::normalize(this->pointB - this->pointA);
    }
   
    inline const glm::mat4& get_matrix() override {
        this->matrix = glm::mat4(1.0f); 
        glm::vec3 speed_vector = this->direction * this->speed;
        this->pointA += speed_vector;

        if ((direction.x > 0 && pointA.x >= pointB.x) || 
            (direction.x < 0 && pointA.x <= pointB.x) || 
            (direction.y > 0 && pointA.y >= pointB.y) || 
            (direction.y < 0 && pointA.y <= pointB.y) || 
            (direction.z > 0 && pointA.z >= pointB.z) || 
            (direction.z < 0 && pointA.z <= pointB.z)) 
        {
            direction *= -1.0f; 
        }

        matrix = glm::translate(this->matrix, this->pointA);
        return matrix;
}


};