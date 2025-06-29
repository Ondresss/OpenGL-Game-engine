//Include GLEW
#include"../headers/Application.h"
#include<stdlib.h>

int main(void) {

	Application* app = Application::get_instance();
	app->prepare_scenes();
	app->render();

	delete app;
	exit(EXIT_SUCCESS);
}




