#pragma once
#include "Component.h"

class AutoDestroyComponent : public Component {
 public:
  float seconds;
  float remain;

  AutoDestroyComponent(float _seconds) : seconds(_seconds), remain(_seconds) {}

  void Update() override;
};
