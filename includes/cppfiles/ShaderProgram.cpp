#include"../headers/ShaderProgram.h"


ShaderProgram::ShaderProgram(const char *vertexFile, const char *fragmentFile){

    this->loader = new ShaderLoader(vertexFile,fragmentFile,&this->programID);
    this->camera = nullptr;
}
void ShaderProgram::useProgram() {
    glUseProgram(this->programID);
}
void ShaderProgram::update(Subject* subject) {
    if(Camera* cameraPtr = dynamic_cast<Camera*>(subject)) {
        this->setMat4Uniform(this->camera->get_view_matrix(),"viewMatrix");
        this->setMat4Uniform(this->camera->get_projection_matrix(),"projectionMatrix"); 
        this->setVec3(this->camera->get_position(),"viewPosition");
    }   
    if(BaseLight* source = dynamic_cast<BaseLight*>(subject)) {
        this->setInt(this->lights.size(),"no_lights");
        for(int i = 0; i < this->lights.size();i++) {
            std::string current_light = "lights[" + std::to_string(i) + "]";

            if(PointLight* point_light = dynamic_cast<PointLight*>(this->lights.at(i))) {
                this->setInt(1,current_light + ".type");
                this->setVec3(point_light->get_position(),current_light + ".position");
                this->setVec3(point_light->get_color(),current_light + ".color");
                this->setFloat(point_light->get_constant(),current_light + ".constant");
                this->setFloat(point_light->get_linear(),current_light + ".linear");
                this->setFloat(point_light->get_quadratic(),current_light + ".quadratic");
                continue;

            }
            if(Reflector* reflector = dynamic_cast<Reflector*>(this->lights.at(i))) {
                if(reflector->is_reflecting()) {
                    this->setInt(2,current_light + ".type");
                    this->setVec3(reflector->get_direction(),current_light + ".direction");
                    this->setVec3(reflector->get_position(),current_light + ".position");
                    this->setFloat(reflector->get_constant(),current_light + ".constant");
                    this->setFloat(reflector->get_linear(),current_light + ".linear");
                    this->setFloat(reflector->get_quadratic(),current_light + ".quadratic");
                    this->setFloat(reflector->calculate_inner_cutoff(),current_light + ".innerCutoff");
                    this->setFloat(reflector->calculate_outer_cutoff(),current_light + ".outerCutoff");
                    this->setVec3(reflector->get_color(),current_light + ".color");

                } else {
                    this->setInt(0,current_light + ".type");
                }
                continue;
            }
            if(DirectionalLight* dir_light = dynamic_cast<DirectionalLight*>(subject)) {
                if(dir_light->is_shinning()) {
                    this->setInt(3,current_light + ".type");
                    this->setVec3(dir_light->get_color(),current_light + ".color");
                    this->setVec3(dir_light->get_direction(),current_light + ".direction");
                } else {
                    this->setInt(0,current_light + ".type");
                }
            }
        }
    }
}

void ShaderProgram::setVec3(const glm::vec3& vect,const std::string &name) {
    this->useProgram();
    unsigned int location = glGetUniformLocation(this->programID,name.c_str());
    if(location == (unsigned)-1) {
        std::cerr << "Could not locate uniform: " << name << "\n";
    }
    glUniform3fv(location,1,&vect[0]);
}
void ShaderProgram::setFloat(float num,const std::string& name) {
    this->useProgram();
    unsigned int location = glGetUniformLocation(this->programID,name.c_str());
    if(location == (unsigned)-1) {
        std::cerr << "Could not locate uniform: " << name << "\n";
    }
    glUniform1f(location,num);
}

void ShaderProgram::setMat4Uniform(const glm::mat4& matrix,const std::string &name) {
    this->useProgram();
    unsigned int location = glGetUniformLocation(this->programID,name.c_str());
    if(location == (unsigned)-1) {
        std::cerr << "Could not locate uniform: " << name << "\n";
    }
    glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(matrix));
}

void ShaderProgram::setInt(int num,const std::string& name) {
    this->useProgram();
    unsigned int location = glGetUniformLocation(this->programID,name.c_str());
    if(location == (unsigned)-1) {
        std::cerr << "Could not locate uniform: " << name << "\n";
    }
    glUniform1i(location, num);
}