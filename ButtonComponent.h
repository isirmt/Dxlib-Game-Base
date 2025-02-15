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
    std::vector<Callback> onHoverStartFuncs;
    std::vector<Callback> onHoverFuncs;
    std::vector<Callback> onHoverEndFuncs;
    std::vector<Callback> onClickStartFuncs;
    std::vector<Callback> onClickFuncs;
    std::vector<Callback> onClickEndFuncs;

    std::shared_ptr<IMouseCameraSelector> cameraSelector;

    bool isHovering = false;
    bool isClicked = false;
    
    ButtonComponent() {}

    void AddOnHoverStartListener(Callback callback);
    void AddOnHoverListener(Callback callback);
    void AddOnHoverEndListener(Callback callback);
    void AddOnClickStartListener(Callback callback);
    void AddOnClickListener(Callback callback);
    void AddOnClickEndListener(Callback callback);

    void Update(GameObject& obj) override;
};

