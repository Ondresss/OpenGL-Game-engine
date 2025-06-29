#include "Renderer.h"
#include "AbstractModel.h"
#include "Mesh.h"
#include "Vertex.h"
#include <vector>
#include "Texture.h"
#pragma once

class MeshedModel : public AbstractModel  {
private:
    std::vector<Mesh> meshes;
public:
    MeshedModel(std::vector<Mesh>& meshes);
    MeshedModel(std::vector<Mesh>& meshes,Texture* texture);
    MeshedModel(std::vector<Mesh>& meshes,Material* material);

    inline void bind_VAO(Mesh mesh) {glBindVertexArray(mesh.VAO);}

    inline std::vector<Mesh>& get_meshes() {return this->meshes;}
    inline void set_texture(Texture* texture) {this->texture = texture;}
    inline Texture* get_texture() {return this->texture;}



};