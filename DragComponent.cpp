#include "DragComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Rect2DComponent.h"
#include "DxLib.h"
#include "IMouseCoordinateConverter.h"
#include "UIMouseCoordinateConverter.h"

void DragComponent::Update()
{
    if (!mouseProvider) {
#ifdef _DEBUG
        OutputDebugString((GetGameObject()->name + std::string(" [Warning] mouseProvider is not provided in DragComponent.\n")).c_str());
#endif
    }

    auto transform = GetGameObject()->GetComponent<TransformComponent>();
    auto rect = GetGameObject()->GetComponent<Rect2DComponent>();
    if (!transform || !rect) return;

    std::shared_ptr<IMouseCoordinateConverter> converter;
    if (cameraSelector) {
        converter = cameraSelector->GetCurrentMouseConverter(GetGameObject()->GetLayer());
    }
    else {
        converter = std::make_shared<UIMouseCoordinateConverter>();
    }

    if (!converter) return;

    int mouseScreenX, mouseScreenY;

    if (mouseProvider) {
        mouseProvider->GetMousePosition(mouseScreenX, mouseScreenY);
    }
    else {
        GetMousePoint(&mouseScreenX, &mouseScreenY);
    }
    int worldMouseX, worldMouseY;
    converter->Convert(mouseScreenX, mouseScreenY, worldMouseX, worldMouseY);

	// Transform・Rect2Dを利用
    int objX = static_cast<int>(transform->worldX);
    int objY = static_cast<int>(transform->worldY);
    int width = static_cast<int>(rect->sx * transform->worldScaleX);
    int height = static_cast<int>(rect->sy * transform->worldScaleY);

    bool isOver = (worldMouseX >= objX && worldMouseX <= objX + width &&
        worldMouseY >= objY && worldMouseY <= objY + height);

    bool currentLeftDown = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

    if (!dragging) {
        // クリック開始時にドラッグ開始
        if (!wasLeftMouseDown && currentLeftDown && isOver) {
            dragging = true;
            offsetX = worldMouseX - objX;
            offsetY = worldMouseY - objY;
        }
    }
    else {
        if (currentLeftDown) {
            transform->localX = static_cast<float>(worldMouseX - offsetX);
            transform->localY = static_cast<float>(worldMouseY - offsetY);

        }
        else {
			// マウスボタン離した時
            dragging = false;
        }
    }

    wasLeftMouseDown = currentLeftDown;
}
