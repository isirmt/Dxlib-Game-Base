#pragma once
#include "Component.h"
class Rect2DComponent :
	public Component
{
public:
	float sx, sy;
	unsigned int color;
	
	Rect2DComponent(float _sx, float _sy, unsigned int _color) : sx(_sx), sy(_sy), color(_color) {}

	void Render(GameObject& obj) override;
};

