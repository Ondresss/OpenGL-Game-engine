#include "../headers/SkyBox.h"

int SkyBox::load(const std::vector<std::string>& faces) {
    unsigned int id_text = 0;
    glGenTextures(1, &id_text);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id_text);

    for (unsigned int i = 0; i < faces.size(); i++) {
        int width, height, channels;
        unsigned char* data = SOIL_load_image(faces[i].c_str(), &width, &height, &channels, SOIL_LOAD_RGB);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            SOIL_free_image_data(data);
        } else {
            std::cerr << "Failed to load cubemap texture: " << faces[i] << std::endl;
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0); 
            glDeleteTextures(1, &id_text);         
            exit(EXIT_FAILURE);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return id_text;
}

void SkyBox::bindAll() {
    this->model->bind_VAO();
    this->bind();
}

SkyBox::SkyBox(const std::vector<std::string>& faces) : Texture() {
    this->id = this->load(faces);
    if (this->id == -1) { 
        std::cerr << "Skybox texture loading failed.\n";
        exit(EXIT_FAILURE);
    }
    this->texture_unit = TextureUnitManager::get_next_unit();
    std::cout << "SkyBos unit in constr is: " << this->texture_unit << std::endl;
    this->bind();
    this->model = new Model(sky,36 * 3 * sizeof(float),36);
    this->model->create_VAO();
    this->model->prepare(0);
    this->program = nullptr;
}
