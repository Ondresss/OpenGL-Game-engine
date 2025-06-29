#pragma once
#include"Renderer.h"
#include "VertexBuffer.h"
#include<vector>
#include "Material.h"
#include "Texture.h"
#include "SkyBoxModel.h"

class Model {

    VertexBuffer* VB;    
    unsigned int VAO;
    unsigned int points;
    Material* material;
    Texture* texture;

public:
    inline Model(const std::vector<float>& vertexes) {
        this->VB = new VertexBuffer((void*)&vertexes[0],vertexes.size() * sizeof(float));
    }
    inline Model(float* vertexes,size_t len,unsigned int points) : points(points) {
        this->VB = new VertexBuffer(vertexes,len);
        this->material = nullptr;
        this->texture = nullptr;

    }
    inline Model(float* vertexes,size_t len,unsigned int points,Material* material) : points(points) {
        this->VB = new VertexBuffer(vertexes,len);
        this->material = material;
        this->texture = nullptr;

    }
    inline Model(float* vertexes,size_t len,unsigned int points,Texture* texture) : points(points) {
        this->VB = new VertexBuffer(vertexes,len);
        this->texture = texture;
        this->material = nullptr;
    }
    inline void bind_model() const {this->VB->Bind();}
    inline void unbind_model() const {this->VB->UnBind();}
    void prepare(int flag);
    inline void bind_VAO()  {glBindVertexArray(0);glBindVertexArray(this->VAO);} 
    inline void create_VAO() {
        glGenVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);
        if(this->VAO == 0) {
            printf("Could not init VAO\n");
            exit(EXIT_FAILURE);
        }
    }
    inline unsigned int get_points() const {return this->points;}
    inline void switch_material(Material* material) {this->material = material;}
    inline const Material* get_material() const {return this->material;}
    inline Texture* get_active_texture() const {return this->texture;}
    inline bool has_texture() const {return nullptr != this->texture;}
    inline bool has_material() const {return nullptr != this->material;}
};