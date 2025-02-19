#include "DragComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "DxLib.h"
#include "IMouseCoordinateConverter.h"
#include "UIMouseCoordinateConverter.h"
#include "Application.h"

void DragComponent::Update()
{
    if (!mouseProvider) {
#ifdef _DEBUG
        OutputDebugString((GetGameObject()->name + std::string(" [Warning] mouseProvider is not provided in DragComponent.\n")).c_str());
#endif
    }

    auto transform = GetGameObject()->GetComponent<TransformComponent>();
    auto collider = GetGameObject()->GetComponent<ColliderComponent>();
    if (!transform || !collider) return;

    int x = static_cast<int>(transform->worldX);
    int y = static_cast<int>(transform->worldY);

    int mouseScreenX, mouseScreenY;
    if (mouseProvider) {
        mouseProvider->GetMousePosition(mouseScreenX, mouseScreenY);
    }
    else {
        GetMousePoint(&mouseScreenX, &mouseScreenY);
    }

    std::shared_ptr<IMouseCoordinateConverter> converter;
    if (cameraSelector) {
        converter = cameraSelector->GetCurrentMouseConverter(GetGameObject()->GetLayer());
    }
    else {
        converter = std::make_shared<UIMouseCoordinateConverter>();
    }

    if (!converter) return;

    int convertedX, convertedY;
    converter->Convert(mouseScreenX, mouseScreenY, convertedX, convertedY);

    bool isOver = collider->Contains(static_cast<float>(convertedX), static_cast<float>(convertedY));

    bool currentLeftDown = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

    if (!dragging) {
        // クリック開始時にドラッグ開始
        if (!wasLeftMouseDown && currentLeftDown && isOver) {
            if (!ignoreLayerCheck) {
                auto topObj = Application::GetInstance().GetTopGameObjectAtPoint();
                if (!topObj || topObj.get() != GetGameObject().get()) {
                    wasLeftMouseDown = currentLeftDown;
                    return;
                }
            }

            dragging = true;
            offsetX = convertedX - x;
            offsetY = convertedY - y;
        }
    }
    else {
        if (currentLeftDown) {
            transform->localX = static_cast<float>(convertedX - offsetX);
            transform->localY = static_cast<float>(convertedY - offsetY);

        }
        else {
			// マウスボタン離した時
            dragging = false;
        }
    }

    wasLeftMouseDown = currentLeftDown;
}
