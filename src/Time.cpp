#include "Time.h"

float Time::deltaTime = 0.f;
float Time::targetFPS = 60.f;
bool Time::unlimitedFPS = true;
std::shared_ptr<Time> instance_ = nullptr;
