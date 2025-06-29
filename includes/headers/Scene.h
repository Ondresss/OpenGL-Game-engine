#include"DrawableObject.h"
#include"Renderer.h"
#include "Cube.h"
#include "PointLight.h"
#include "ShaderProgramFactory.h"
#include "Transformation.h"
#include "TransformationComposite.h"
#include "ScaleTransformation.h"
#include "RotationTransformation.h"
#include "TranslationTransformation.h"
#include "BaseLight.h"
#include <vector>
#include "SkyBox.h"
#pragma once
class Scene {
protected:
    std::vector<DrawableObject*> drawables;
    std::string name;
    std::vector<BaseLight*> lights;
    SkyBox* skyBox;
public:
    Scene(const std::string& name) : name(name),skyBox(nullptr){};
    Scene(const std::string&name,SkyBox* skyBox) : name(name),skyBox(skyBox) {}
    inline void load_drawable(DrawableObject* obj) {
        this->drawables.push_back(obj);
    }
    inline void load_drawable(const std::vector<DrawableObject*>& objs) {
        this->drawables.assign(objs.begin(),objs.end());
    }
    void present();
    inline const std::string& get_scene_name() const {return this->name;}
    inline void remove_last() {this->drawables.pop_back();}
    inline void change_scene_name(const std::string& name) {this->name = name;}
    inline  std::vector<DrawableObject*> get_drawables() {return this->drawables;}
    glm::vec3 generate_random_color();
    inline void add_light(PointLight* light) {this->lights.push_back(light);}

    void handle_observer(ShaderProgram* program);

    void switch_day();

    void generate_random_lights(int no_lights);
    const std::vector<BaseLight*>& get_ligts() {return this->lights;} 

    inline void set_skybox_shader(ShaderProgram* program) {this->skyBox->set_skybox_shaderProgram(program);}
    void draw_skybox();


};