#include "Renderer.h"
#include "Transformation.h"
#pragma once
class TransformationFactory {

private:
    TransformationFactory() = delete;
public:

    static Transformation* get_transformation();

};