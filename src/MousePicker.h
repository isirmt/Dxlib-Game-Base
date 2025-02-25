#pragma once
#include <memory>
#include <vector>

#include "GameObject.h"
#include "Scene.h"

class MousePicker {
 public:
  std::shared_ptr<GameObject> GetTopGameObjectAtPoint(
      const std::vector<std::shared_ptr<Scene>>& scenes, int mouseScreenX,
      int mouseScreenY,
      const std::shared_ptr<MouseCameraSelector>& cameraSelector);
};
