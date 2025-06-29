#include "Renderer.h"
#include "Scene.h"
#include "RotationTransformation.h"
#include "TranslationTransformation.h"
#include "ScaleTransformation.h"
#include "ShaderProgramFactory.h"
#include "sphere.h"
#include "StaticData.h"
#include "gift.h"
#include "suzi_flat.h"
#include "DynamicRotationTransformation.h"
class GeometricScene : public Scene {
public:
    inline GeometricScene(std::string scene_name = "geometric_scene") : Scene(scene_name) {}
    inline ~GeometricScene() {
        for(const auto& obj : this->drawables) {
            delete obj;
        }
    }
    static GeometricScene* generate_cube_scene_random(Camera* camera);
    static GeometricScene* generate_cube_test_scene(Camera* camera,ShaderProgram* program);
    static GeometricScene* generate_triangle_scene(Camera* camera,ShaderProgram* shader_program);

};