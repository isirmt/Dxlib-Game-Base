#include "MouseCameraSelector.h"

#include "Application.h"
#include "Camera2DComponent.h"
#include "CameraMouseCoordinateConverter.h"
#include "DxLib.h"
#include "InputManager.h"

std::shared_ptr<CameraMouseCoordinateConverter>
MouseCameraSelector::GetCurrentMouseConverter() {
  int mouseX, mouseY;
  if (auto mouseProvider = InputManager::GetInstance().GetMouseProvider()) {
    mouseProvider->GetMousePosition(mouseX, mouseY);
  } else {
    GetMousePoint(&mouseX, &mouseY);
  }

  std::shared_ptr<Camera2DComponent> selectedCamera = nullptr;

  for (auto& camObj : cameras) {
    auto camComp = camObj->GetComponent<Camera2DComponent>();
    if (!camComp) continue;

    int dx = camComp->destX;
    int dy = camComp->destY;
    int dWidth = camComp->destWidth;
    int dHeight = camComp->destHeight;

    if (mouseX >= dx && mouseX <= dx + dWidth && mouseY >= dy &&
        mouseY <= dy + dHeight) {
      if (!selectedCamera ||
          (camComp->GetGameObject()->GetLayer() >
           selectedCamera->GetGameObject()->GetLayer()) ||
          (camComp->GetGameObject()->GetLayer() ==
               selectedCamera->GetGameObject()->GetLayer() &&
           (camComp->GetGameObject()->GetOrderInLayer() >
            selectedCamera->GetGameObject()->GetOrderInLayer()))) {
        selectedCamera = camComp;
      }
    }
  }

  if (selectedCamera) {
    return std::make_shared<CameraMouseCoordinateConverter>(selectedCamera);
  } else {
    return nullptr;
  }
}

std::shared_ptr<CameraMouseCoordinateConverter>
MouseCameraSelector::GetCurrentMouseConverter(int targetLayer) {
  int mouseX, mouseY;
  if (auto mouseProvider = InputManager::GetInstance().GetMouseProvider()) {
    mouseProvider->GetMousePosition(mouseX, mouseY);
  } else {
    GetMousePoint(&mouseX, &mouseY);
  }

  std::shared_ptr<Camera2DComponent> selectedCamera = nullptr;

  for (auto& camObj : cameras) {
    auto camComp = camObj->GetComponent<Camera2DComponent>();
    if (!camComp) continue;

    if (camComp->renderLayer != targetLayer) continue;

    int dx = camComp->destX;
    int dy = camComp->destY;
    int dWidth = camComp->destWidth;
    int dHeight = camComp->destHeight;

    if (mouseX >= dx && mouseX <= dx + dWidth && mouseY >= dy &&
        mouseY <= dy + dHeight) {
      if (!selectedCamera ||
          (camComp->GetGameObject()->GetLayer() >
           selectedCamera->GetGameObject()->GetLayer()) ||
          (camComp->GetGameObject()->GetLayer() ==
               selectedCamera->GetGameObject()->GetLayer() &&
           (camComp->GetGameObject()->GetOrderInLayer() >
            selectedCamera->GetGameObject()->GetOrderInLayer()))) {
        selectedCamera = camComp;
      }
    }
  }

  if (selectedCamera) {
    return std::make_shared<CameraMouseCoordinateConverter>(selectedCamera);
  } else {
    return nullptr;
  }
}
