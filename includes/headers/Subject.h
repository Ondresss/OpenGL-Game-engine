#include "Renderer.h"
#include <vector>
#include <algorithm>
#pragma once
class Observer;
class Subject {
protected:
    std::vector<Observer*> observers;
public:
    Subject() = default;
    virtual ~Subject() = default;
    void notify();
    void add(Observer* observer);
    void remove(Observer* observer);
};