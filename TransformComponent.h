#pragma once
#include "Component.h"

class TransformComponent :
	public Component
{
public:
	int x, y;

	TransformComponent(int x0, int y0) : x(x0), y(y0) {}
};

