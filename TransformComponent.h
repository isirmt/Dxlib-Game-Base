#pragma once
#include <list>

#include "Component.h"

class TransformComponent : public Component {
 public:
  std::shared_ptr<GameObject> parent;
  std::list<std::shared_ptr<GameObject>> children;

  // ローカル変換
  float localX, localY;
  float localRotation;
  float localScaleX, localScaleY;

  // ワールド変換
  float worldX, worldY;
  float worldRotation;
  float worldScaleX, worldScaleY;

  TransformComponent(float x = 0.f, float y = 0.f, float rotation = 0.f,
                     float scaleX = 1.f, float scaleY = 1.f)
      : localX(x),
        localY(y),
        localRotation(rotation),
        localScaleX(scaleX),
        localScaleY(scaleY),
        worldX(x),
        worldY(y),
        worldRotation(rotation),
        worldScaleX(scaleX),
        worldScaleY(scaleY) {}

  void SetParent(std::shared_ptr<GameObject> newParent);

  void UpdateWorldTransform();

  void Update() override;
};
