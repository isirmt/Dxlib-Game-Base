#pragma once
#include "Component.h"
class Camera2DComponent :
	public Component
{
public:

	int srcX, srcY, srcWidth, srcHeight;
	int destX, destY, destWidth, destHeight;
	int renderLayer;

	Camera2DComponent(int _srcX, int _srcY, int _srcWidth, int _srcHeight,
		int _destX, int _destY, int _destWidth, int _destHeight, int _renderLayer = 0)
		: srcX(_srcX), srcY(_srcY), srcWidth(_srcWidth), srcHeight(_srcHeight),
		destX(_destX), destY(_destY), destWidth(_destWidth), destHeight(_destHeight),
		renderLayer(_renderLayer)
	{
	}

	void Render(int offscreenHandle) const;

};

