#pragma once
#include <memory>
#include <vector>

#include "GameObject.h"
#include "IMouseCoordinateConverter.h"

class IMouseCameraSelector {
 public:
  std::vector<std::shared_ptr<GameObject>> cameras;

  std::shared_ptr<IMouseCoordinateConverter> GetCurrentMouseConverter();
  std::shared_ptr<IMouseCoordinateConverter> GetCurrentMouseConverter(
      int targetLayer);
};
