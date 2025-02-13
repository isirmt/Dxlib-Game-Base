#define _USE_MATH_DEFINES

#include "TransformComponent.h"
#include "GameObject.h"
#include <cmath>

void TransformComponent::UpdateWorldTransform(GameObject& obj)
{
	// parent‚Ìƒ|ƒCƒ“ƒ^‚ðlock
	if (auto parentPtr = obj.parent.lock()) {
		if (auto parentTransform = parentPtr->GetComponent<TransformComponent>()) {
			float pX = parentTransform->worldX;
			float pY = parentTransform->worldY;
			float pRot = parentTransform->worldRotation;
			float pScaleX = parentTransform->worldScaleX;
			float pScaleY = parentTransform->worldScaleY;

			float rad = pRot * (static_cast<float>(M_PI) / 180.0f);
			float rotatedX = localX * pScaleX * cos(rad) - localY * pScaleY * sin(rad);
			float rotatedY = localX * pScaleX * sin(rad) + localY * pScaleY * cos(rad);

			worldX = pX + rotatedX;
			worldY = pY + rotatedY;
			worldRotation = pRot + localRotation;
			worldScaleX = pScaleX * localScaleX;
			worldScaleY = pScaleY * localScaleY;
		}
		else {
			worldX = localX;
			worldY = localY;
			worldRotation = localRotation;
			worldScaleX = localScaleX;
			worldScaleY = localScaleY;
		}
	}
	else {
		worldX = localX;
		worldY = localY;
		worldRotation = localRotation;
		worldScaleX = localScaleX;
		worldScaleY = localScaleY;
	}
}

void TransformComponent::Update(GameObject& obj)
{
	UpdateWorldTransform(obj);
}
