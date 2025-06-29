#include "Renderer.h"
#include "Model.h"
#include <SOIL/SOIL.h>
#include "Mesh.h"
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include "Vertex.h"
#include "AbstractModel.h"
#include "MeshedModel.h"
#pragma once
class MeshedModelFactory {
private:
    inline MeshedModelFactory() = default;
    static std::vector<Mesh> loadMeshes(const std::string& path);
public:
    static MeshedModel* loadModel(const std::string& path);
};
