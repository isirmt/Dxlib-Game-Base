#pragma once
#include "Component.h"
class Rect2DComponent :
	public Component
{
public:
	unsigned int sx, sy;
	unsigned int color;
	
	Rect2DComponent(unsigned int _sx, unsigned int _sy, unsigned int _color) : sx(_sx), sy(_sy), color(_color) {}

	void Render(GameObject& obj) override;
};

