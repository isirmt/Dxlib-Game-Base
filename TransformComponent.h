#pragma once
#include "Component.h"

class TransformComponent :
	public Component
{
public:
	// ���[�J���ϊ�
	float localX, localY;
	float localRotation;
	float localScaleX, localScaleY;

	// ���[���h�ϊ�
	float worldX, worldY;
	float worldRotation;
	float worldScaleX, worldScaleY;

	TransformComponent(float x = 0, float y = 0, float rotation = 0, float scaleX = 1, float scaleY = 1)
		: localX(x), localY(y), localRotation(rotation), localScaleX(scaleX), localScaleY(scaleY),
		worldX(x), worldY(y), worldRotation(rotation), worldScaleX(scaleX), worldScaleY(scaleY) {
	}

	void UpdateWorldTransform(GameObject& obj);

	void Update(GameObject& obj) override;
};

