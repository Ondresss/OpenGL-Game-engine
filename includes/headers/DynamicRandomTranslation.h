#include "Renderer.h"
#include "TransformationBase.h"


class DynamicRandomTranslation : public TransformationBase {


private:
    glm::vec3 movement;
public:

    inline DynamicRandomTranslation() {
        float x = static_cast<float>(std::rand() % 2);
        float y = static_cast<float>(std::rand() % 2);
        float z = static_cast<float>(std::rand() % 2);
        this->movement = glm::normalize(glm::vec3(x,y,z));
    }
    const glm::mat4& get_matrix() override;
};
