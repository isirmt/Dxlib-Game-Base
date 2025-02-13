#pragma once
#include "Component.h"
#include <functional>
#include <memory>
#include <vector>
#include "IMouseCoordinateConverter.h"
#include "UIMouseCoordinateConverter.h"
#include "IMouseCameraSelector.h"

using Callback = std::function<void()>;

class ButtonComponent :
    public Component
{
public:
    std::vector<Callback> onClickFuncs;
    std::shared_ptr<IMouseCameraSelector> cameraSelector;
    
    ButtonComponent() {}

    void AddOnClickListener(Callback callback);

    void Update(GameObject& obj) override;
};

