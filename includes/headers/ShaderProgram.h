#pragma once
#include<vector>
#include<string>
#include<utility>
#include "./Observer.h"
#include "./Camera.h"
#include "ShaderLoader.h"
#include "PointLight.h"
#include "BaseLight.h"
#include "Reflector.h"
#include "DirectionalLight.h"
#pragma once
class PointLight;
class ShaderProgram : public Observer {
private:
    unsigned int programID;
    Camera* camera;
    ShaderLoader* loader;
    std::vector<BaseLight*> lights;
public:
    inline ~ShaderProgram() {
        delete this->camera;
        delete this->loader;
    };
    ShaderProgram(const char *vertexFile, const char *fragmentFile);
    void useProgram();
    void update(Subject* subject) override;
    void setMat4Uniform(const glm::mat4& matrix,const std::string& name);
    void setVec3(const glm::vec3& vect,const std::string& name);
    void setFloat(float num,const std::string& name);
    void setInt(int num,const std::string& name);
    inline void addSubject(Camera* camera) {this->camera = camera;}
    inline void addSubject(BaseLight* light) {this->lights.push_back(light);}
    
};