#include "MousePicker.h"

#include <algorithm>
#include <tuple>

#include "Camera2DComponent.h"
#include "CameraMouseCoordinateConverter.h"
#include "ColliderComponent.h"
#include "MouseCameraSelector.h"

std::shared_ptr<GameObject> MousePicker::GetTopGameObjectAtPoint(
    const std::vector<std::shared_ptr<Scene>>& scenes, int mouseScreenX,
    int mouseScreenY,
    const std::shared_ptr<MouseCameraSelector>& cameraSelector) {
  struct Clickable {
    std::shared_ptr<GameObject> obj;
    int cameraLayer = 0;
    int cameraOrder = 0;
    int objOrder = 0;
    std::shared_ptr<CameraMouseCoordinateConverter> converter;
  };

  std::vector<Clickable> clickables;

  for (const auto& scene : scenes) {
    for (const auto& obj : scene->GetGameObjects()) {
      if (!obj->IsActive()) continue;
      auto collider = obj->GetComponent<ColliderComponent>();
      if (!collider) continue;

      if (obj->GetComponent<Camera2DComponent>()) continue;

      Clickable c;

      c.converter = cameraSelector->GetCurrentMouseConverter(obj->GetLayer());
      if (!c.converter) {
        continue;
      }

      auto cameraObj = c.converter->pCamera_->GetGameObject();

      c.obj = obj;
      c.objOrder = obj->GetOrderInLayer();
      c.cameraLayer = cameraObj->GetLayer();
      c.cameraOrder = cameraObj->GetOrderInLayer();

      clickables.push_back(c);
    }
  }

  std::sort(clickables.begin(), clickables.end(),
            [](const Clickable& a, const Clickable& b) {
              return std::tie(a.cameraLayer, a.cameraOrder, a.objOrder) >
                     std::tie(b.cameraLayer, b.cameraOrder, b.objOrder);
            });

  int convertedX, convertedY;
  for (auto& c : clickables) {
    if (!c.converter) continue;
    c.converter->Convert(mouseScreenX, mouseScreenY, convertedX, convertedY);
    if (c.obj->GetComponent<ColliderComponent>()->Contains(
            static_cast<float>(convertedX), static_cast<float>(convertedY))) {
      return c.obj;
    }
  }
  return nullptr;
}
