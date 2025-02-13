#pragma once
#include "IMouseCoordinateConverter.h"
#include "Camera2DComponent.h"
#include <memory>

class CameraMouseCoordinateConverter :
	public IMouseCoordinateConverter
{
	std::shared_ptr<Camera2DComponent> pCamera_;

public:
	CameraMouseCoordinateConverter(std::shared_ptr<Camera2DComponent> _pCamera)
		: pCamera_(_pCamera) {
	}

	void Convert(int screenX, int screenY, int& outX, int& outY) {
		int relativeX = screenX - pCamera_->destX;
		int relativeY = screenY - pCamera_->destY;

		float scaleX = static_cast<float>(pCamera_->srcWidth) / pCamera_->destWidth;
		float scaleY = static_cast<float>(pCamera_->srcHeight) / pCamera_->destHeight;

		outX = pCamera_->srcX + static_cast<int>(relativeX * scaleX);
		outY = pCamera_->srcY + static_cast<int>(relativeY * scaleY);
	}
};

