#include"../headers/Scene.h"

void Scene::present() {

   this->draw_skybox();
   glClear ( GL_DEPTH_BUFFER_BIT );
   for(auto& obj : this->drawables) {
        for(auto& light : this->lights) {
                light->shine();
        }
        obj->draw();
   }
}

glm::vec3 Scene::generate_random_color() {

        float r = static_cast<float>(std::rand() % 50) / 255.0f;  
        float g = 0.4f + static_cast<float>(std::rand() % 155) / 255.0f; 
        float b = static_cast<float>(std::rand() % 100) / 255.0f;   
        return glm::vec3(r, g, b);

}

void Scene::handle_observer(ShaderProgram* program) {
        for(auto& light : this->lights) {
                light->add(program);
                program->addSubject(light);
        }
}
void Scene::generate_random_lights(int no_lights) {
        for(int i = 0; i < no_lights ;i++) {
                float x = static_cast<float>(std::rand() % 100) - 100;  
                float y = 5; 
                float z = static_cast<float>(std::rand() % 50) - 50;
                glm::vec3 new_vec = glm::vec3(x,y,z);
                this->lights.push_back(new PointLight(new_vec,glm::vec3(1.0f,1.0f,1.0f)));                           
        }
        DirectionalLight* dir_light = new DirectionalLight(glm::vec3(-0.5, -1.0, -0.3));
        this->lights.push_back(dir_light);
}

void Scene::switch_day() {
        for(auto& light : this->lights) {
                if(DirectionalLight* dir_light = dynamic_cast<DirectionalLight*>(light)) {
                        dir_light->toggle_shinning();
                }
        }
}
void Scene::draw_skybox() {
        if(this->skyBox->has_program()) {
                std::cout << "SkyBox unit: " << this->skyBox->get_unit() << std::endl;
                this->skyBox->get_program()->setInt(this->skyBox->get_unit(),"skybox");
        } else {
                std::cerr << "SkyBox doesnt have shader program\n";
                exit(EXIT_FAILURE);
        }
        this->skyBox->get_model()->bind_VAO();
        glDrawArrays(GL_TRIANGLES, 0, this->skyBox->get_model()->get_points());
        
}