#pragma once
#include "Renderer.h"
#include "DrawableObject.h"
#include <vector>
#include<ctime>
#include "TransformationFactory.h"
#include "tree.h"
#include "sphere.h"
#include "Application.h"
#include "plain.h"
#include "Cube.h"
#include "RotationTransformation.h"
#include "TranslationTransformation.h"
#include "ScaleTransformation.h"
#include "ShaderProgramFactory.h"
#include "Scene.h"
#include "DynamicRotationTransformation.h"
#include "DynamicSideTranslation.h"
#include "SkyBox.h"
#include "SkyBoxModel.h"
class Application;
class Forest : public Scene {

private:
    DrawableObject* rain;
    bool isRaining;
public:

    Forest() : Scene("forest_scene",new SkyBox({"./posx.jpg","./negx.jpg","./posy.jpg","./negy.jpg","./posz.jpg","./negz.jpg"})), rain(nullptr),isRaining(false){};

    void plant_random();
    static Forest* generate_random(Camera* camera);
    void start_rain(Camera* camera);
    DrawableObject* raining();
    inline bool is_raining() const {return this->isRaining;}
    inline void stop_raining() {this->isRaining = !this->isRaining;}
    void rotate_trees(int no_trees);
};