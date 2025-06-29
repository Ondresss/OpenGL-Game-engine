#include "TransformationBase.h"
#pragma once
class BezierCurveTransformation : public TransformationBase {

private:
    glm::mat4 A;
    glm::mat4x3 control_point_matrix;
    float t;
    float delta;
public:
    BezierCurveTransformation(glm::vec3& pointA,glm::vec3& pointB,glm::vec3& pointC,glm::vec3& pointD,float t,float delta);

    const glm::mat4& get_matrix() override;

};