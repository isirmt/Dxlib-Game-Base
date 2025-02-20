#include "DragComponent.h"

#include "Application.h"
#include "ColliderComponent.h"
#include "DxLib.h"
#include "GameObject.h"
#include "IMouseCoordinateConverter.h"
#include "InputManager.h"
#include "TransformComponent.h"

void DragComponent::Update() {
  auto defaultTransform = GetGameObject()->GetComponent<TransformComponent>();
  auto collider = GetGameObject()->GetComponent<ColliderComponent>();
  if (!defaultTransform || !collider) return;

  auto activeTransform = targetTransform ? targetTransform : defaultTransform;

  int x = static_cast<int>(activeTransform->worldX);
  int y = static_cast<int>(activeTransform->worldY);

  int mouseScreenX, mouseScreenY;
  if (auto mouseProvider = InputManager::GetInstance().GetMouseProvider()) {
    mouseProvider->GetMousePosition(mouseScreenX, mouseScreenY);
  } else {
    GetMousePoint(&mouseScreenX, &mouseScreenY);
    OutputDebugString(
        (GetGameObject()->name +
         std::string(
             " [Warning] mouseProvider is not provided in DragComponent.\n"))
            .c_str());
  }

  std::shared_ptr<IMouseCoordinateConverter> converter;
  if (cameraSelector) {
    converter =
        cameraSelector->GetCurrentMouseConverter(GetGameObject()->GetLayer());
  }

  if (!converter) {
    if (dragging && cancelDraggingOnConverterNull) {
      dragging = false;
    }
    return;
  }

  int convertedX, convertedY;
  converter->Convert(mouseScreenX, mouseScreenY, convertedX, convertedY);

  bool isOver = collider->Contains(static_cast<float>(convertedX),
                                   static_cast<float>(convertedY));

  bool currentLeftDown = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

  if (!dragging) {
    // クリック開始時にドラッグ開始
    if (!wasLeftMouseDown && currentLeftDown && isOver) {
      if (!ignoreLayerCheck) {
        auto topObj = Application::GetInstance().GetTopGameObjectAtPoint();
        if (!topObj || topObj.get() != GetGameObject().get()) {
          wasLeftMouseDown = currentLeftDown;
          return;
        }
      }

      dragging = true;
      offsetX = convertedX - x;
      offsetY = convertedY - y;
    }
  } else {
    if (currentLeftDown) {
      activeTransform->localX = static_cast<float>(convertedX - offsetX);
      activeTransform->localY = static_cast<float>(convertedY - offsetY);
    } else {
      // マウスボタン離した時
      dragging = false;
    }
  }

  wasLeftMouseDown = currentLeftDown;
}
