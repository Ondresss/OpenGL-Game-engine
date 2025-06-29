#include "Renderer.h"
#pragma once

class Camera;
class Mouse {
private:
    glm::vec3 direction;
    float pitchAngle;
    float yawAngle;
    float sensitivity;
    bool firstUse;
    double lastX;
    double lastY;
    float rotationSpeed;
    Camera* camera;
public:
    inline Mouse(const glm::vec3& direction,float pitchAngle,float yawAngle,float sensitivity,Camera* camera,float rotationSpeed) : direction(direction),pitchAngle(pitchAngle),yawAngle(yawAngle),
    sensitivity(sensitivity),firstUse(true),lastX(0.0f),lastY(0.0f),camera(camera),rotationSpeed(rotationSpeed){}
    void update(double xPos,double yPos);
    inline const glm::vec3& get_direction() const {return this->direction;}
    inline float get_sensitivity() const {return this->sensitivity;}

    void rotate_left();
    void rotate_up();
    void rotate_down();
    void rotate_right();

};