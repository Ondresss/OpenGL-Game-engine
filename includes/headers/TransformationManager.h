#include "Renderer.h"
#include"Transformation.h"
#include <vector>
class TransformationManager {

private:
    std::vector<Transformation*> transformations;
public:

    TransformationManager() = default;
    std::vector<Transformation*> get();
    inline void register_transformations(const std::vector<Transformation*>& transformations) {this->transformations.assign(transformations.begin(),transformations.end());}

};