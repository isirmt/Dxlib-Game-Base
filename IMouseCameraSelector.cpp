#include "IMouseCameraSelector.h"

#include "Application.h"
#include "Camera2DComponent.h"
#include "CameraMouseCoordinateConverter.h"
#include "DxLib.h"
#include "InputManager.h"

std::shared_ptr<IMouseCoordinateConverter>
IMouseCameraSelector::GetCurrentMouseConverter() {
  int mouseX, mouseY;
  if (auto mouseProvider = InputManager::GetInstance().GetMouseProvider()) {
    mouseProvider->GetMousePosition(mouseX, mouseY);
  } else {
    GetMousePoint(&mouseX, &mouseY);
  }
#ifdef _DEBUG
  printfDx("Mouse: %d %d\n", mouseX, mouseY);
#endif

  std::shared_ptr<Camera2DComponent> selectedCamera = nullptr;

  // renderLayerが最も高いものを選択
  for (auto& camObj : cameras) {
    auto camComp = camObj->GetComponent<Camera2DComponent>();
    if (!camComp) continue;

    int dx = camComp->destX;
    int dy = camComp->destY;
    int dWidth = camComp->destWidth;
    int dHeight = camComp->destHeight;
#ifdef _DEBUG
    printfDx("Camera: (%d, %d) W%d H%d, RenderLayer: %d\n", dx, dy, dWidth,
             dHeight, camComp->renderLayer);
#endif
    if (mouseX >= dx && mouseX <= dx + dWidth && mouseY >= dy &&
        mouseY <= dy + dHeight) {
      if (!selectedCamera ||
          camComp->renderLayer > selectedCamera->renderLayer) {
        selectedCamera = camComp;
      }
    }
  }

  if (selectedCamera) {
#ifdef _DEBUG
    printfDx("[GLOBAL] Target Camera: RenderLayer: %d\n",
             selectedCamera->renderLayer);
#endif
    return std::make_shared<CameraMouseCoordinateConverter>(selectedCamera);
  } else {
    return nullptr;
  }
}

std::shared_ptr<IMouseCoordinateConverter>
IMouseCameraSelector::GetCurrentMouseConverter(int targetLayer) {
  int mouseX, mouseY;
  if (auto mouseProvider = InputManager::GetInstance().GetMouseProvider()) {
    mouseProvider->GetMousePosition(mouseX, mouseY);
  } else {
    GetMousePoint(&mouseX, &mouseY);
  }
#ifdef _DEBUG
  printfDx("Mouse: %d %d\n", mouseX, mouseY);
#endif

  std::shared_ptr<Camera2DComponent> selectedCamera = nullptr;

  // 対象レイヤーのカメラのみ
  for (auto& camObj : cameras) {
    if (camObj->GetLayer() != targetLayer) continue;

    auto camComp = camObj->GetComponent<Camera2DComponent>();
    if (!camComp) continue;

    int dx = camComp->destX;
    int dy = camComp->destY;
    int dWidth = camComp->destWidth;
    int dHeight = camComp->destHeight;
#ifdef _DEBUG
    printfDx("Camera (Layer %d): (%d, %d) W%d H%d, RenderLayer: %d\n",
             targetLayer, dx, dy, dWidth, dHeight, camComp->renderLayer);
#endif
    if (mouseX >= dx && mouseX <= dx + dWidth && mouseY >= dy &&
        mouseY <= dy + dHeight) {
      if (!selectedCamera ||
          camComp->renderLayer > selectedCamera->renderLayer) {
        selectedCamera = camComp;
      }
    }
  }

  if (selectedCamera) {
#ifdef _DEBUG
    printfDx("Target Camera: RenderLayer: %d\n", selectedCamera->renderLayer);
#endif
    return std::make_shared<CameraMouseCoordinateConverter>(selectedCamera);
  } else {
    return nullptr;
  }
}
