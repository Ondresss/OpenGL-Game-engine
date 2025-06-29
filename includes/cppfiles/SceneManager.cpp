#include"../headers/SceneManager.h"

void SceneManager::set_scene(const std::string& name) {
    auto found_Scene = this->scenes.find(name);
    if (found_Scene != this->scenes.end()) {
        this->current_scene = found_Scene->second;
    } else {
        std::cerr << "Scene '" << name << "' not found!\n";
    }
}
void SceneManager::draw_current() {
    if (this->current_scene) {
        this->current_scene->present();
    } else {
        std::cerr << "No scene is currently set!\n";
    }
}
void SceneManager::create_scene(const std::string& name,const std::vector<DrawableObject*>& objs) {
   for (auto obj : objs) {
        if (obj == nullptr) {
            std::cerr << "Warning: Null Drawable pointer found in scene '" << name << "'\n";
            return; 
        }
    }
    Scene* new_scene = new Scene(name); 
    new_scene->load_drawable(objs);
    this->scenes[name] = new_scene;
   
    
}
Scene* SceneManager::get_next_scene() {
    if(this->scenes.empty()) {
        perror("There isnt a scene in the application\n");
        exit(EXIT_FAILURE);
    }
    if(this->currentSceneIterator == this->scenes.end()) {
        this->currentSceneIterator = this->scenes.begin();
    } else {
        this->currentSceneIterator++;
        if(this->currentSceneIterator == this->scenes.end()) {
            this->currentSceneIterator = this->scenes.begin();
        }
    }
   return this->currentSceneIterator->second;

}
void SceneManager::add_scene(Scene* scene) {
    this->scenes[scene->get_scene_name()] = scene;
}