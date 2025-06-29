#include "Renderer.h"
#include <SOIL/SOIL.h>
#pragma once
#include "TextureUnitManager.h"
class Texture {

protected:
    unsigned int id;
    int texture_unit;
public:
    Texture(const char* path);
    Texture() = default;
    inline ~Texture() {
        glDeleteTextures(1, &id);
    }
    void bind();
    int load(const char* path);
    inline int get_unit() const {return this->texture_unit;}

};