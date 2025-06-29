#include "../headers/Mouse.h"
#include "../headers/Camera.h"

void Mouse::update(double xPos,double yPos) {
    if(this->firstUse) {
        this->lastX = xPos;
        this->lastY = yPos;
        this->firstUse = false;
    }
    double offsetX = xPos - this->lastX;
    double offsetY = this->lastY - yPos;
    this->lastX = xPos;
    this->lastY = yPos;

    double sensitivity = 0.2f;
    offsetX *= sensitivity;
    offsetY *= sensitivity;

    this->pitchAngle += offsetY;
    this->yawAngle += offsetX;
    if(this->pitchAngle > 89.0f)
        this->pitchAngle = 89.0f;
    if(this->pitchAngle < -89.0f)
        this->pitchAngle = -89.0f;
    glm::vec3 directionNew(1.0f);
    directionNew.x = cos(glm::radians(this->yawAngle)) * cos(glm::radians(this->pitchAngle));
    directionNew.y = sin(glm::radians(this->pitchAngle));
    directionNew.z = sin(glm::radians(this->yawAngle)) * cos(glm::radians(this->pitchAngle));
    this->direction = glm::normalize(directionNew);
    this->camera->notify();

}

void Mouse::rotate_right() {
    this->direction = glm::normalize(glm::rotate(glm::mat4(1.0f),glm::radians(-this->rotationSpeed),glm::vec3(0.0f,1.0f,0.0f)) * glm::vec4(this->direction,1.0f) );
}
void Mouse::rotate_down() {
    glm::vec3 right = glm::cross(this->direction,glm::vec3(0.0f,1.0f,0.0f));
    this->direction = glm::normalize(glm::rotate(glm::mat4(1.0f),-this->rotationSpeed,right) * glm::vec4(this->direction,1.0f));
}
void Mouse::rotate_left() {
    this->direction = glm::normalize(glm::rotate(glm::mat4(1.0f),glm::radians(this->rotationSpeed),glm::vec3(0.0f,1.0f,0.0f)) * glm::vec4(this->direction,1.0f) );
}
void Mouse::rotate_up() {
    glm::vec3 right = glm::cross(this->direction,glm::vec3(0.0f,1.0f,0.0f));
    this->direction = glm::normalize(glm::rotate(glm::mat4(1.0f),this->rotationSpeed,right) * glm::vec4(this->direction,1.0f));
}