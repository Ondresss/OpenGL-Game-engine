#include "../headers/Renderer.h"

void GLclearErrors() {
    while (!glGetError());
}

void GLcheckError() {
    while (GLenum err = glGetError()) {
        std::cerr << "Error occured " << err << "\n";
    }
    exit(EXIT_FAILURE);
}