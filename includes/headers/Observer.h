#include <string>
#include "Renderer.h"
#include "Subject.h"
#pragma once
class Subject;
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(Subject* subject) = 0;

};