#pragma once
#include"./Renderer.h"
#include "./DrawableObject.h"
#include<vector>
#include<utility>
#include "StaticData.h"
#include "SceneManager.h"
#include"./tree.h"
#include "./plain.h"
#include "TransformationFactory.h"
#include"bushes.h"
#include"sphere.h"
#include "Forest.h"
#include "CameraController.h"
#include "GeometricScene.h"
class Forest;
class Application {
private:
    static Application* instance;
    std::unique_ptr<SceneManager> scene_manager;
    std::pair<int,int> window_dimensions;
    std::pair<float,float> actual_dimensions;
    GLFWwindow* app_window; 
    CameraController* camera_controller;
    inline Application(int window_width,int window_height) : app_window(nullptr) {
        this->window_dimensions = std::make_pair(window_width,window_height);
        this->actual_dimensions = std::make_pair(-1,-1);
        this->scene_manager = std::make_unique<SceneManager>();
        this->init();
    }
public:
    static void staticKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if(key == GLFW_KEY_Q && action == GLFW_PRESS) {
            glfwWindowShouldClose(window);
            glfwTerminate();
            exit(EXIT_SUCCESS);
            return;
        }
        Application::get_instance()->keyCallback(key, scancode, action, mods);
        Application::get_instance()->get_controller()->handle_keys(key,scancode,action,mods);
    }
    static void staticMouseCallback(GLFWwindow* window, double xpos, double ypos) {
        Application::get_instance()->get_controller()->hadle_mouse(xpos,ypos);
    }
    inline ~Application() {
        glfwDestroyWindow(this->app_window);
        glfwTerminate();
    }
    void keyCallback(int key,int scancode,int action,int mods);
    inline static Application* get_instance() {
        if(!instance) {
            instance = new Application(600,600);
            return instance;
        } 
        return instance;
    }
    void init();
    void prepare_scenes();
    void render();
    inline std::pair<float,float>& get_actual_dimensions() {return this->actual_dimensions;} 
    inline CameraController* get_controller() {return this->camera_controller;}
    inline const std::pair<float,float>& get_dimensions() {return this->actual_dimensions;}
    static void handle_framebuffer_callback(GLFWwindow* window, int width, int height);

};