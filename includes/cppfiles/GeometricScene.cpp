#include "../headers/GeometricScene.h"

GeometricScene* GeometricScene::generate_cube_scene_random(Camera* camera) {

    GeometricScene* geometric_scene = new GeometricScene();
    geometric_scene->generate_random_lights(10);
    Model* model = new Model(sphere,2880 * 6 * sizeof(float),2880,new Material(glm::vec3(0.0, 0.1, 0.9),glm::vec3(0.2, 0.5, 0.5),7.0f,glm::vec3(0.3,1,0.4)));
    model->create_VAO();
    model->prepare(1);
    Model* gift_model = new Model(gift,66624 * 6 * sizeof(float),66624,new Material(glm::vec3(0.7, 0.1, 0.8),glm::vec3(0.2, 0.3, 0.2),7.0f,glm::vec3(0.3,0.6,0.4)));
    gift_model->create_VAO();
    gift_model->prepare(1);

    Model* suzi_flat_model = new Model(suziFlat,17424 * 6 * sizeof(float),17424,new Material(glm::vec3(0.8, 0.1, 0.4),glm::vec3(0.5, 0.5, 0.1),7.0f,glm::vec3(0.1,0.1,0.9)));
    suzi_flat_model->create_VAO();
    suzi_flat_model->prepare(1);


    Model* suzie_other = new Model(suziFlat,2904 * 6 * sizeof(float),2904,new Material(glm::vec3(0.3, 0.6, 0.2),glm::vec3(0.2, 0.8, 0.1),127.0f,glm::vec3(0.7,0.6,0.4)));
    suzie_other->create_VAO();
    suzie_other->prepare(1);

    auto phong = ShaderProgramFactory::get_phong_shader();
    auto blinn = ShaderProgramFactory::get_blinn_shader();
    geometric_scene->handle_observer(phong);
    geometric_scene->handle_observer(blinn);
    camera->add(phong);
    camera->add(blinn);
    phong->addSubject(camera);
    blinn->addSubject(camera);

    auto sphere = new DrawableObject(phong,model,glm::vec3(0.4,0.0,0.8));
    auto gift = new DrawableObject(blinn,gift_model,glm::vec3(0.2,0.5,0.8));
    auto suzi_flat = new DrawableObject(phong,suzi_flat_model,glm::vec3(0.7,0.1,0.3));
    auto suzie_next = new DrawableObject(phong,suzie_other,glm::vec3(0.1,0.4,0.2));
    geometric_scene->load_drawable({sphere,gift,suzi_flat,suzie_next});

    std::vector<Transformation*> transformations;
    for (size_t i = 0; i < geometric_scene->get_drawables().size();i++) {
        size_t rand_trees = std::rand() % 20 + 10; 

        for (size_t i = 0; i < rand_trees; i++) {
            float rand_x = static_cast<float>(std::rand() % 100 - 100); 
            float rand_y = static_cast<float>(std::rand() % 7) - 4 ;  
            float rand_z = static_cast<float>(std::rand() % 50 - 50); 
            float scale_factor = static_cast<float>(((std::rand() % 20) + 40) / 10.0f); 
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

        geometric_scene->get_drawables().at(i)->switch_transformations(transformations);
        transformations.clear();
    }

    return geometric_scene;
}

GeometricScene* GeometricScene::generate_cube_test_scene(Camera* camera,ShaderProgram* program) {

    GeometricScene* geometric_scene = new GeometricScene("test_cube_scene");
    geometric_scene->add_light(new PointLight(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,1.0f,1.0f)));
    Model* model = new Model(sphere,2880 * 6 * sizeof(float),2880,new Material(glm::vec3(0.7, 0.7, 0.7),glm::vec3(0.4, 0.5, 0.5),32.0f,glm::vec3(0.3,0.6,0.4)));
    model->create_VAO();
    model->prepare(1);


    auto sphere = new DrawableObject(program,model,glm::vec3(0.0f,1.0f,1.0f));

    camera->add(program);
    program->addSubject(camera);

    geometric_scene->handle_observer(program);

    geometric_scene->load_drawable(sphere);
    std::vector<Transformation*> transformations;

    TransformationComposite* trans_composite = new TransformationComposite();
    trans_composite->add(new TranslationTransformation(glm::vec3(-4.0,0.0,0.0)))->add(new ScaleTransformation(glm::vec3(0.8,0.8,0.8))); 

    Transformation* trans = new Transformation();
    trans->add_composite(trans_composite);
    transformations.push_back(trans);

    TransformationComposite* trans_composite2 = new TransformationComposite();
    trans_composite2->add(new TranslationTransformation(glm::vec3(0,-4.0,0.0)))->add(new ScaleTransformation(glm::vec3(0.8,0.8,0.8))); 
    Transformation* trans2 = new Transformation();
    trans2->add_composite(trans_composite2);
    transformations.push_back(trans2);

    TransformationComposite* trans_composite3 = new TransformationComposite();
    trans_composite3->add(new TranslationTransformation(glm::vec3(4.0,0.0,0.0)))->add(new ScaleTransformation(glm::vec3(0.8,0.8,0.8))); 
    Transformation* trans3 = new Transformation();
    trans3->add_composite(trans_composite3);
    transformations.push_back(trans3);

    TransformationComposite* trans_composite4 = new TransformationComposite();
    trans_composite4->add(new TranslationTransformation(glm::vec3(0.0,4.0,0.0)))->add(new ScaleTransformation(glm::vec3(0.8,0.8,0.8))); 
    Transformation* trans4 = new Transformation();
    trans4->add_composite(trans_composite4);
    transformations.push_back(trans4);

    geometric_scene->get_drawables().at(0)->switch_transformations(transformations);
    return geometric_scene;
}
GeometricScene* GeometricScene::generate_triangle_scene(Camera* camera,ShaderProgram* program) {
    GeometricScene* geometric_scene = new GeometricScene("test_triangle_scene");

    geometric_scene->add_light(new PointLight(glm::vec3(0.0f,0.0f,-4.0f),glm::vec3(1.0f,1.0f,1.0f)));
    geometric_scene->handle_observer(program);
    auto triangle_model = new Model(points,3 * 6 * sizeof(float),3,new Material(glm::vec3(0.9, 0.9, 0.9),glm::vec3(1, 1, 1),127.0f,glm::vec3(0.8,0.8,0.8)));
    triangle_model->create_VAO();
    triangle_model->prepare(1);
    auto triangle = new DrawableObject(program,triangle_model,glm::vec3(1.0f,0.5f,0.8f));
    

    camera->add(program);
    program->addSubject(camera);


    std::vector<Transformation*> transformations;

    TransformationComposite* trans_composite = new TransformationComposite();
    trans_composite->add(new TranslationTransformation(glm::vec3(0.0,0.0,0.0)))->add(new ScaleTransformation(glm::vec3(8,8,8)))->add(new DynamicRotationTransformation(45.0f,glm::vec3(0.0f,1.0f,0.0f))); 

    Transformation* trans = new Transformation();
    trans->add_composite(trans_composite);
    transformations.push_back(trans);

    triangle->switch_transformations(transformations);
    geometric_scene->load_drawable(triangle);

    return geometric_scene;
}

