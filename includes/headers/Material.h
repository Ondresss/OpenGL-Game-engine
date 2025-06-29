#include "Renderer.h"


class Material {

private:
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 ambient;
    float shininnes;
public:

    inline Material(glm::vec3 dif,glm::vec3 spec,float shin,glm::vec3 ambient) : diffuse(dif),specular(spec),shininnes(shin),ambient(ambient) {}
    inline const glm::vec3& get_diffuse() const {return this->diffuse;}
    inline const glm::vec3& get_specular() const {return this->specular;}
    inline float get_shininnes() const {return this->shininnes;}
    inline const glm::vec3& get_ambient() const {return this->ambient;}

};