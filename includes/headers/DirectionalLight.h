#include "Renderer.h"
#include "BaseLight.h"

class DirectionalLight : public BaseLight {

private:
    glm::vec3 direction;
    bool shinning;
public:
    inline DirectionalLight(glm::vec3 direction) : BaseLight(glm::vec3(1.0f,1.0f,1.0f)),direction(direction),shinning(false) {}

    inline void shine() override {
        this->notify();
    }

    const glm::vec3& get_direction() const {return this->direction;}
    inline void toggle_shinning() {this->shinning = !this->shinning;}
    inline bool is_shinning() {return this->shinning;}

};