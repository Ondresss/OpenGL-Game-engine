#include "../headers/Forest.h"

void Forest::plant_random() {

    std::vector<Transformation*> transformations;
    for (size_t i = 0; i < 2;i++) {
        if(!this->drawables.at(i)) {
            std::cerr << "Tre wasnt found in the forest\n";
            exit(EXIT_FAILURE);
        }
        size_t rand_trees = 400; 

        for (size_t i = 0; i < rand_trees; i++) {
            float rand_x = static_cast<float>(std::rand() % 200 - 200); 
            float rand_y = static_cast<float>(std::rand() % 7) - 4 ;  
            float rand_z = static_cast<float>(std::rand() % 100 - 50); 
            float scale_factor = static_cast<float>((std::rand() % 20) / 10.0f); 
            float angle = static_cast<float>(std::rand() % 180);  
            float rand_red = static_cast<float>(std::rand() % 150) / 255.0f;   
            float rand_green = static_cast<float>(std::rand() % 256) / 255.0f; 
            float rand_blue = static_cast<float>(std::rand() % 150) / 255.0f; 

            TransformationComposite* trans_composite = new TransformationComposite();
            trans_composite->add(new TranslationTransformation(glm::vec3(rand_x,rand_y,rand_z)))->add(new ScaleTransformation(glm::vec3(scale_factor,scale_factor,scale_factor)));
            Transformation* trans = new Transformation();
            trans->add_composite(trans_composite);
            transformations.push_back(trans);
        }

        for(int i = 0; i < 20;i++) {
            float rand_x = static_cast<float>(std::rand() % 100 - 100); 
            float rand_y = static_cast<float>(std::rand() % 7) - 4 ;  
            float rand_z = static_cast<float>(std::rand() % 50 - 50); 
            float scale_factor = static_cast<float>((std::rand() % 20) / 10.0f); 
            float angle = static_cast<float>(std::rand() % 180);  
            float rand_red = static_cast<float>(std::rand() % 150) / 255.0f;   
            float rand_green = static_cast<float>(std::rand() % 256) / 255.0f; 
            float rand_blue = static_cast<float>(std::rand() % 150) / 255.0f; 

            TransformationComposite* trans_composite = new TransformationComposite();
            trans_composite->add(new TranslationTransformation(glm::vec3(rand_x,rand_y,rand_z)))->add(new ScaleTransformation(glm::vec3(scale_factor,scale_factor,scale_factor)))
            ->add(new DynamicRotationTransformation(45.0f,glm::vec3(0.0f,1.0f,0.0f)));
            Transformation* trans = new Transformation();
            trans->add_composite(trans_composite);
            transformations.push_back(trans);
        }


        this->drawables.at(i)->switch_transformations(transformations);
        transformations.clear();
    }
    transformations.clear();
    TransformationComposite* trans_com = new TransformationComposite();
    trans_com->add(new ScaleTransformation(glm::vec3(310.0f,1.0f,310.0f)))->add(new TranslationTransformation(glm::vec3(0.0f,0.5f,0.0f)))->add(new RotationTransformation(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
    Transformation* trans = new Transformation(); 
    trans->add_composite(trans_com);
    transformations.push_back(trans);
    this->drawables.at(this->drawables.size()-1)->switch_transformations(transformations);
}

Forest* Forest::generate_random(Camera* camera) {
    Forest* forest = new Forest();
    auto skybox_program = ShaderProgramFactory::get_skybox_constant_shader();
    camera->add(skybox_program);
    skybox_program->addSubject(camera);

    forest->set_skybox_shader(skybox_program);

    forest->generate_random_lights(1);
    Model* tree_model = new Model(tree,92814 * 6 * sizeof(float),92814,new Material(glm::vec3(0.8f, 0.8f, 0.2f),glm::vec3(0.7, 0.7, 0.7),6.0f,glm::vec3(0.3,0.3,0.2)));
    tree_model->create_VAO();
    tree_model->prepare(1);	
    Model* bush_model = new Model(bushes,8730 * 6 * sizeof(float),8730,new Material(glm::vec3(0.3, 0.6, 0.2),glm::vec3(0.2, 0.3, 0.2),7.0,glm::vec3(0.2,0.2,0.2)));
    bush_model->create_VAO();
    bush_model->prepare(1);
    Model* plain_model = new Model(plain,6 * 8 * sizeof(float),6,new Texture("./textures/grass.png"));
    plain_model->create_VAO();
    plain_model->prepare(2);
    Model* cube_model_shinning = new Model(cubeVertices,36 * 6 * sizeof(float),36,new Material(glm::vec3(0.2, 0.2, 0.2), glm::vec3(1.0, 1.0, 1.0), 128,glm::vec3(0.6,0.6,0.6)));
    cube_model_shinning->create_VAO();
    cube_model_shinning->prepare(1);
    auto phong_shader = ShaderProgramFactory::get_phong_shader();
    auto phong_shader_texture = ShaderProgramFactory::get_phong_texture_shader();
    camera->add(phong_shader);
    camera->register_reflector_observers(phong_shader);
    camera->register_reflector_observers(phong_shader_texture);
    camera->add(phong_shader_texture);
    phong_shader->addSubject(camera);
    phong_shader_texture->addSubject(camera);
    forest->handle_observer(phong_shader); 

    forest->handle_observer(phong_shader_texture);

    auto tree = new DrawableObject(phong_shader,tree_model,forest->generate_random_color());
    auto bush = new DrawableObject(phong_shader,bush_model,forest->generate_random_color());
    auto grass = new DrawableObject(phong_shader_texture,plain_model,glm::vec3(0.0f, 1.0f, 0.0f));
    forest->load_drawable(tree);
    forest->load_drawable(bush);

    for(auto& light : forest->get_ligts()) {
        if(PointLight* point_light = dynamic_cast<PointLight*>(light)) {
            auto blud = new DrawableObject(phong_shader,cube_model_shinning,glm::vec3(1.0f,1.0f,0.0f));
            TransformationComposite* trans_com2 = new TransformationComposite();
            trans_com2->add(new TranslationTransformation(point_light->get_position()))->add(new ScaleTransformation(glm::vec3(0.4f,1.0f,0.2f)))->add(new DynamicSideTranslation(point_light->get_position(),glm::vec3(0.0,0.0,0.0),0.1f));
            Transformation* trans2 = new Transformation(); 
            trans2->add_composite(trans_com2);
            blud->switch_transformations({trans2});
            blud->set_light_source(light);
            forest->load_drawable(blud);
        }
    }

    forest->load_drawable(grass);
    forest->plant_random();
    return forest;
}
void Forest::start_rain(Camera* camera) {

}
DrawableObject* Forest::raining() {
  
}
void Forest::rotate_trees(int no_trees) {
    
}