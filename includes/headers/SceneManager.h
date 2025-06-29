#include "Renderer.h"
#include "Scene.h"
#include <map>
class SceneManager {
private:
    Scene* current_scene;
    std::map<std::string,Scene*> scenes;
    std::map<std::string, Scene*>::iterator currentSceneIterator;
public:
    SceneManager() : currentSceneIterator(this->scenes.begin()){};
    void set_scene(const std::string& name);
    void draw_current();
    void create_scene(const std::string& name,const std::vector<DrawableObject*>& objs );
    inline Scene* get_current_scene() {
        return this->current_scene;
    }
    inline void add_to_draw(DrawableObject* obj) {this->current_scene->load_drawable(obj);}
    inline void remove_last() {this->current_scene->remove_last();}

    inline void toggle_day_current() {
        if(this->current_scene) {
            this->current_scene->switch_day();
        }
    }

    Scene* get_next_scene();
    void add_scene(Scene* scene);
};