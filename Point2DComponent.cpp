#include "Point2DComponent.h"

#include "DxLib.h"
#include "GameObject.h"
#include "TransformComponent.h"

void Point2DComponent::Render() {
  auto transform = GetGameObject()->GetComponent<TransformComponent>();
  if (!transform) return;

  float x = transform->worldX;
  float y = transform->worldY;

  DrawPixel(static_cast<int>(x), static_cast<int>(y), color);
}
