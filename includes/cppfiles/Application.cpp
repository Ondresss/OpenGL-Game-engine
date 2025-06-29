#include "../headers/Application.h"

Application* Application::instance = nullptr;



void Application::keyCallback(int key,int scancode,int action,int mods) {
	if(key == GLFW_KEY_T && action == GLFW_PRESS) {
		this->scene_manager->toggle_day_current();
	}
	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		Scene* scene = this->scene_manager->get_next_scene();
		if(!scene) {
			perror("Error switching scene\n");
			exit(EXIT_FAILURE);
		}
		printf("%s\n\n\n\n",scene->get_scene_name().c_str());
		this->scene_manager->set_scene(scene->get_scene_name());
	}
	if(key == GLFW_KEY_R && action == GLFW_PRESS) {
		auto forest = static_cast<Forest*>(glfwGetWindowUserPointer(this->app_window));
		forest->stop_raining();
	}

}
void Application::init() {
	std::srand(std::time(nullptr));  
    if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);  
	
	this->app_window = glfwCreateWindow(800, 600, "ZPG-MIC0487", NULL, NULL);
	if (!this->app_window){
		printf("Window failed\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->app_window);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	glewInit();

	printf("OpenGL Version: %s\n",glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    int width,height;
	glfwGetFramebufferSize(this->app_window, &width, &height);
    this->actual_dimensions = std::make_pair(width,height);
	float ratio = this->actual_dimensions.first / (float)this->actual_dimensions.second;
	glViewport(0, 0, this->actual_dimensions.first, this->actual_dimensions.second);
	//glfwSetInputMode(this->app_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(this->app_window,Application::staticKeyCallback);
	glfwSetCursorPosCallback(this->app_window, Application::staticMouseCallback);  
	glfwSetFramebufferSizeCallback(this->app_window, Application::handle_framebuffer_callback);
	this->camera_controller = new CameraController(ratio);

}

void Application::render() {
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	this->scene_manager->set_scene("forest_scene");
	auto forest = static_cast<Forest*>(glfwGetWindowUserPointer(this->app_window));
    while (!glfwWindowShouldClose(this->app_window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->camera_controller->move_camera();
		this->scene_manager->draw_current();
        glfwSwapBuffers(this->app_window);
        glfwPollEvents();
    }
}
void Application::prepare_scenes() {

	Forest* forest = Forest::generate_random(this->camera_controller->get_camera());																																																																																																																																																																					
	GeometricScene* geometric_scene = GeometricScene::generate_cube_scene_random(this->camera_controller->get_camera());
	GeometricScene* geometric_scene_cube_text = GeometricScene::generate_cube_test_scene(this->camera_controller->get_camera(),ShaderProgramFactory::get_phong_shader());
	GeometricScene* geometric_triangle_scene = GeometricScene::generate_triangle_scene(this->camera_controller->get_camera(),ShaderProgramFactory::get_phong_shader());


	glfwSetWindowUserPointer(this->app_window,forest);
	this->scene_manager->add_scene(forest);
	this->scene_manager->add_scene(geometric_scene);
	this->scene_manager->add_scene(geometric_scene_cube_text);
	this->scene_manager->add_scene(geometric_triangle_scene);
	
}

void Application::handle_framebuffer_callback(GLFWwindow* window, int width, int height) {
	Application* app = Application::get_instance();
	app->get_actual_dimensions().first = width;
	app->get_actual_dimensions().second = height;
	glViewport(0,0,width,height);
	app->get_controller()->update_camera_ratio(static_cast<float>(width) / static_cast<float>(height));
}