#include "../headers/Texture.h"


void Texture::bind() {
    glActiveTexture(GL_TEXTURE0 + this->texture_unit); 
    std::cout << "Binded with: " << this->texture_unit << std::endl;
    glBindTexture(GL_TEXTURE_2D, this->id); 
}

Texture::Texture(const char* path) {
    this->id = this->load(path);
    if (id != 0) { 
        this->texture_unit = TextureUnitManager::get_next_unit(); 
        this->bind(); 
    } else {
        std::cerr << "Texture creation failed for path: " << path << "\n";
        exit(EXIT_FAILURE);
    }
}

int Texture::load(const char* path) {
    std::cout << "Loading texture from path: " << path << std::endl;
    int width, height, channels;
    unsigned char* image = SOIL_load_image(path, &width, &height, &channels, SOIL_LOAD_RGBA);
    if (!image) {
        std::cerr << "Failed to load texture: " << SOIL_last_result() << std::endl;
        return 0;  
    }
    unsigned int id_text;
    glGenTextures(1, &id_text);
    glBindTexture(GL_TEXTURE_2D, id_text);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SOIL_free_image_data(image);

    return id_text;
}