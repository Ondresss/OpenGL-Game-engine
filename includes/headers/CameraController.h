#include "Renderer.h"
#include "Camera.h"


class CameraController {
private:
    Camera* camera;
public:
    CameraController(float ratio);
    void handle_keys(int key, int scancode, int action, int mods);
    void hadle_mouse(int xPos,int yPos);
    inline void set_camera(Camera* camera) {this->camera = camera;}
    inline Camera* get_camera() {return this->camera;}
    inline void move_camera() {this->camera->move();}
    inline void update_camera_ratio(float ratio) {this->camera->set_ratio(ratio);}
    inline void update_camera_FOV(float FOV) {this->camera->set_FOV(FOV);}
    inline void use_camera_reflector() {this->camera->use_reflector();}

};