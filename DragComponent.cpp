#include "DragComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Rect2DComponent.h"
#include "DxLib.h"
#include "IMouseCoordinateConverter.h"
#include "UIMouseCoordinateConverter.h"

void DragComponent::Update(GameObject& obj)
{
    auto transform = obj.GetComponent<TransformComponent>();
    auto rect = obj.GetComponent<Rect2DComponent>();
    if (!transform || !rect) return;

    std::shared_ptr<IMouseCoordinateConverter> converter;
    if (cameraSelector) {
        converter = cameraSelector->GetCurrentMouseConverter();
    }
    else {
        converter = std::make_shared<UIMouseCoordinateConverter>();
    }

    int mouseScreenX, mouseScreenY;
    GetMousePoint(&mouseScreenX, &mouseScreenY);
    int worldMouseX, worldMouseY;
    converter->Convert(mouseScreenX, mouseScreenY, worldMouseX, worldMouseY);

    // Transform・Rect2Dを利用
    int objX = static_cast<int>(transform->worldX);
    int objY = static_cast<int>(transform->worldY);
    int width = static_cast<int>(rect->sx * transform->worldScaleX);
    int height = static_cast<int>(rect->sy * transform->worldScaleY);

    bool isOver = (worldMouseX >= objX && worldMouseX <= objX + width &&
        worldMouseY >= objY && worldMouseY <= objY + height);

    if (!dragging) {
        // 左クリックで開始
        if (isOver && (GetMouseInput() & MOUSE_INPUT_LEFT)) {
            dragging = true;
            offsetX = worldMouseX - objX;
            offsetY = worldMouseY - objY;
        }
    }
    else {
        // ドラッグ中
        if (GetMouseInput() & MOUSE_INPUT_LEFT) {
            if (auto trans = obj.GetComponent<TransformComponent>()) {
                trans->localX = static_cast<float>(worldMouseX - offsetX);
                trans->localY = static_cast<float>(worldMouseY - offsetY);
            }
        }
        else {
            // マウスボタン離した時
            dragging = false;
        }
    }
}
