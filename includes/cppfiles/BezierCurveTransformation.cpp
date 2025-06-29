#include "../headers/BezierCurveTransformation.h"


BezierCurveTransformation::BezierCurveTransformation(glm::vec3& pointA,
        glm::vec3& pointB,
        glm::vec3& pointC,
        glm::vec3& pointD,
        float initial_t = 0.0f,
        float step_delta = 0.01f)
        : t(initial_t), delta(step_delta) {
                this->A= glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
                      glm::vec4(3.0, -6.0, 3.0, 0),
                      glm::vec4(-3.0, 3.0, 0, 0),
                      glm::vec4(1, 0, 0, 0));    
                this->control_point_matrix = glm::mat4x3(pointA,pointB,pointC,pointD);                       

}

const glm::mat4& BezierCurveTransformation::get_matrix() {
        this->matrix = glm::mat4(1.0f); 
        glm::vec4 T = glm::vec4(this->t * this->t * this->t,this->t * this->t,this->t,1.0f);
        this->t+=this->delta;
        if(this->t >= 1.0f || this->t <= 0) {
            this->delta*=-1;
        }
        glm::vec3 p = T * this->A * glm::transpose(this->control_point_matrix);
        this->matrix = glm::translate(this->matrix,p);
        return this->matrix;
}