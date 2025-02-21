#include "MousePicker.h"

#include <algorithm>

#include "Camera2DComponent.h"
#include "ColliderComponent.h"
#include "MouseCameraSelector.h"
#include "IMouseCoordinateConverter.h"

std::shared_ptr<GameObject> MousePicker::GetTopGameObjectAtPoint(
    const std::vector<std::shared_ptr<Scene>>& scenes, int mouseScreenX,
    int mouseScreenY,
    const std::shared_ptr<MouseCameraSelector>& cameraSelector) {
  struct Clickable {
    std::shared_ptr<GameObject> obj;
    int effectiveLayer = 0;
    int order = 0;
    std::shared_ptr<IMouseCoordinateConverter> converter;
  };

  std::vector<Clickable> clickables;

  for (const auto& scene : scenes) {
    for (const auto& obj : scene->GetGameObjects()) {
      if (!obj->IsActive()) continue;
      auto collider = obj->GetComponent<ColliderComponent>();
      if (!collider) continue;

      if (obj->GetComponent<Camera2DComponent>()) continue;

      Clickable c;
      c.obj = obj;
      c.order = obj->GetOrderInLayer();
      c.effectiveLayer = obj->GetLayer();

      c.converter = cameraSelector->GetCurrentMouseConverter(obj->GetLayer());
      if (!c.converter) {
        continue;
      }
      clickables.push_back(c);
    }
  }

  std::sort(clickables.begin(), clickables.end(),
            [](const Clickable& a, const Clickable& b) {
              if (a.effectiveLayer == b.effectiveLayer)
                return a.order > b.order;
              return a.effectiveLayer > b.effectiveLayer;
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
