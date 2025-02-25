#include "Camera2DComponent.h"

#include "DxLib.h"
#include "GameObject.h"
#include "TransformComponent.h"

void Camera2DComponent::Update() {
  auto transform = GetGameObject()->GetComponent<TransformComponent>();
  if (!transform) return;

  destX = static_cast<int>(transform->worldX);
  destY = static_cast<int>(transform->worldY);
}

void Camera2DComponent::Render(int offscreenHandle) const {
  DrawRectExtendGraph(destX, destY, destX + destWidth, destY + destHeight, srcX,
                      srcY, srcWidth, srcHeight, offscreenHandle, TRUE);
}
