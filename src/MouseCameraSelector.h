#pragma once
#include <memory>
#include <vector>

#include "GameObject.h"
#include "CameraMouseCoordinateConverter.h"

class MouseCameraSelector {
 public:
  std::vector<std::shared_ptr<GameObject>> cameras;

  std::shared_ptr<CameraMouseCoordinateConverter> GetCurrentMouseConverter();
  std::shared_ptr<CameraMouseCoordinateConverter> GetCurrentMouseConverter(
      int targetLayer);
};
