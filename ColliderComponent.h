#pragma once
#include "Component.h"

class ColliderComponent : public Component {
public:
    float width, height;

    ColliderComponent(float w, float h) : width(w), height(h) {}

    bool Contains(float x, float y);
};
