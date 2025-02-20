#define _USE_MATH_DEFINES

#include "TransformComponent.h"

#include <cmath>

#include "GameObject.h"

void TransformComponent::SetParent(std::shared_ptr<GameObject> newParent) {
  if (auto currentObj = GetGameObject()) {
    if (parent) {
      auto& siblings = parent->GetComponent<TransformComponent>()->children;
      siblings.erase(std::remove(siblings.begin(), siblings.end(), currentObj),
                     siblings.end());
    }
    parent = newParent;
    if (parent) {
      parent->GetComponent<TransformComponent>()->children.push_back(
          currentObj);
      UpdateWorldTransform();
    }
  }
}

void TransformComponent::UpdateWorldTransform() {
  if (parent) {
    if (auto parentTransform = parent->GetComponent<TransformComponent>()) {
      float pX = parentTransform->worldX;
      float pY = parentTransform->worldY;
      float pRot = parentTransform->worldRotation;
      float pScaleX = parentTransform->worldScaleX;
      float pScaleY = parentTransform->worldScaleY;

      float rad = pRot * (static_cast<float>(M_PI) / 180.0f);
      float rotatedX =
          localX * pScaleX * cos(rad) - localY * pScaleY * sin(rad);
      float rotatedY =
          localX * pScaleX * sin(rad) + localY * pScaleY * cos(rad);

      worldX = pX + rotatedX;
      worldY = pY + rotatedY;
      worldRotation = pRot + localRotation;
      worldScaleX = pScaleX * localScaleX;
      worldScaleY = pScaleY * localScaleY;
    } else {
      worldX = localX;
      worldY = localY;
      worldRotation = localRotation;
      worldScaleX = localScaleX;
      worldScaleY = localScaleY;
    }
  } else {
    worldX = localX;
    worldY = localY;
    worldRotation = localRotation;
    worldScaleX = localScaleX;
    worldScaleY = localScaleY;
  }
}

void TransformComponent::Update() { UpdateWorldTransform(); }
