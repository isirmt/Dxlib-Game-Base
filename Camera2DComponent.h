#pragma once
#include "Component.h"
class Camera2DComponent :
	public Component
{
public:

	int srcX, srcY, srcWidth, srcHeight;
	int destX, destY, destWidth, destHeight;

	Camera2DComponent(int _srcX, int _srcY, int _srcWidth, int _srcHeight,
		int _destX, int _destY, int _destWidth, int _destHeight)
		: srcX(_srcX), srcY(_srcY), srcWidth(_srcWidth), srcHeight(_srcHeight),
		destX(_destX), destY(_destY), destWidth(_destWidth), destHeight(_destHeight) {
	}

	void Render(int offscreenHandle) const;

};

