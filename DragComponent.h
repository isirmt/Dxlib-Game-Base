#pragma once
#include "Component.h"
#include "IMouseCameraSelector.h"

class DragComponent : public Component {
public:
	bool wasLeftMouseDown = false;
	bool dragging = false;
	int offsetX = 0;
	int offsetY = 0;

	std::shared_ptr<IMouseCameraSelector> cameraSelector;

	DragComponent() = default;

	void Update() override;
};

