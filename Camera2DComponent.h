#pragma once
#include "Component.h"
class Camera2DComponent :
	public Component
{
public:

	int srcX, srcY, srcWidth, srcHeight;
	int destX = 0, destY = 0, destWidth, destHeight;
	int renderLayer;

	Camera2DComponent(int _srcX, int _srcY, int _srcWidth, int _srcHeight,
		int _destWidth, int _destHeight, int _renderLayer = 0)
		: srcX(_srcX), srcY(_srcY), srcWidth(_srcWidth), srcHeight(_srcHeight),
		destWidth(_destWidth), destHeight(_destHeight),
		renderLayer(_renderLayer)
	{
	}

	void Update() override;
	void Render(int offscreenHandle) const;

};

