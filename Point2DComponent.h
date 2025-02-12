#pragma once
#include "Component.h"

class Point2DComponent :
	public Component
{
public:
	unsigned int color;

	Point2DComponent(unsigned int _color) : color(_color) {};

	void Render(GameObject& obj) override;
};

