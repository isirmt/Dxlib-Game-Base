#pragma once
#include "Component.h"

class PointUIComponent :
	public Component
{
public:
	unsigned int color;

	PointUIComponent(unsigned int _color) : color(_color) {};

	void Render(GameObject& obj) override;
};

