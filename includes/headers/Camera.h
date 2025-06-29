#include"Renderer.h"
#include "Mouse.h"
#include "./Observer.h"
#include "Subject.h"
#include "Mouse.h"
#include "Reflector.h"
#pragma once
class ShaderProgram;
class Mouse;
class Camera : public Subject {
private:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 direction;
    float speed;
    bool moving;
    glm::vec3 movement;
    Mouse* mouse;
    float FOV;
    float ratio;

    Reflector* reflector;
public:
    inline Camera(glm::vec3 position,glm::vec3 up,glm::vec3 direction,float speed,float FOV,float ratio) :Subject(), position(position),up(up),direction(direction),speed(speed),moving(false),movement(glm::vec3(0.0f,0.0f,0.0f)),FOV(FOV),ratio(ratio) {
        this->reflector = new Reflector();
        this->mouse = new Mouse(this->direction,0.0f,-90.0f,0.3,this,20.0f);
    }

    inline const glm::mat4 get_view_matrix() const{
        return glm::lookAt(this->position,this->position + mouse->get_direction(),this->up); 
    }
    inline void set_direction(const glm::vec3& new_direction) {this->direction = glm::normalize(new_direction);}
    inline glm::vec3& get_position() {return this->position;}
    void move_right();
    void move_left();
    void move_forward();
    void move_back();
    void move();
    inline void reset_movement() {this->movement = glm::vec3(0.0f,0.0f,0.0f);}
    inline Mouse* get_mouse() {return this->mouse;}

    inline void set_ratio(float ratio) {this->ratio = ratio;}
    inline void set_FOV(float FOV) {this->FOV = FOV;}

    inline const glm::mat4 get_projection_matrix() const {
        return glm::perspective(this->FOV,this->ratio,0.1f,100.0f);
    }
    inline void use_reflector() {this->reflector->shine();}
    void register_reflector_observers(ShaderProgram* program); 
    inline glm::vec3& get_movement() {return this->movement;}
    

};