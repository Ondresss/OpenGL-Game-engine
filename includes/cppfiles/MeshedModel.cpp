#include "../headers/MeshedModel.h"


MeshedModel::MeshedModel(std::vector<Mesh>& meshes) : AbstractModel() {
    this->meshes.assign(meshes.begin(),meshes.end());
}
MeshedModel::MeshedModel(std::vector<Mesh>& meshes,Material* material) : AbstractModel(material) {
    this->meshes.assign(meshes.begin(),meshes.end());
}
MeshedModel::MeshedModel(std::vector<Mesh>& meshes,Texture* material) : AbstractModel(texture) {
    this->meshes.assign(meshes.begin(),meshes.end());
}