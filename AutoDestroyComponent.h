#pragma once
#include "Component.h"
class AutoDestroyComponent :
    public Component
{
public:
    int milliseconds;
    int remain;

    AutoDestroyComponent(int _milliseconds) : milliseconds(_milliseconds), remain(_milliseconds) {}

    void Update(GameObject& obj) override;
};

