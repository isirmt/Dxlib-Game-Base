#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "IMouseCoordinateConverter.h"

class IMouseCameraSelector
{
public:
	std::vector<std::shared_ptr<GameObject>> cameras;

	std::shared_ptr<IMouseCoordinateConverter> GetCurrentMouseConverter();
};

