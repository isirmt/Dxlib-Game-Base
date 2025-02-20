#pragma once
#include "Component.h"
#include "IMouseCameraSelector.h"

class DragComponent : public Component {
 public:
  bool wasLeftMouseDown = false;
  bool dragging = false;
  int offsetX = 0;
  int offsetY = 0;
  bool ignoreLayerCheck = false;
  bool cancelDraggingOnConverterNull = false;

  std::shared_ptr<class TransformComponent> targetTransform;

  std::shared_ptr<IMouseCameraSelector> cameraSelector;

  DragComponent() = default;

  void Update() override;
};
