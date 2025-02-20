#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "Scene.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "IMouseCoordinateConverter.h"
#include "UIMouseCoordinateConverter.h"
#include "CameraMouseCoordinateConverter.h"
#include "IMouseCameraSelector.h"

class MousePicker {
public:
    std::shared_ptr<GameObject> GetTopGameObjectAtPoint(
        const std::vector<std::shared_ptr<Scene>>& scenes,
        int mouseScreenX,
        int mouseScreenY,
        const std::shared_ptr<IMouseCameraSelector>& cameraSelector);
};
