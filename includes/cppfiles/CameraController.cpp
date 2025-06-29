#include "../headers/CameraController.h"

CameraController::CameraController(float ratio) {
    this->camera = new Camera(glm::vec3(0.0f,0.0f,3.0f),glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),0.4f,45.0f,ratio);
}


void CameraController::handle_keys(int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_W && action == GLFW_PRESS) {
       this->camera->move_forward(); 
	}
	if(key == GLFW_KEY_S && action == GLFW_PRESS) {
		this->camera->move_back();
	}
    if(key == GLFW_KEY_A && action == GLFW_PRESS) {
		this->camera->move_left();
	}
	if(key == GLFW_KEY_D && action == GLFW_PRESS) {
		this->camera->move_right();
	}
    if((key == GLFW_KEY_W || key == GLFW_KEY_S || key == GLFW_KEY_D || key == GLFW_KEY_A ) && action == GLFW_RELEASE) {
       this->camera->reset_movement(); 
	}
	if(key == GLFW_KEY_E && action == GLFW_PRESS) {
		this->use_camera_reflector();
	}
	if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		this->camera->get_mouse()->rotate_right();
	}
	if(key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		this->camera->get_mouse()->rotate_down();
	}
	if(key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		this->camera->get_mouse()->rotate_left();
	}
	if(key == GLFW_KEY_UP && action == GLFW_PRESS) {
		this->camera->get_mouse()->rotate_up();
	}
}

void CameraController::hadle_mouse(int xPos,int yPos) {
    this->camera->get_mouse()->update(xPos,yPos);
}

