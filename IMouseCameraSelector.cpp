#include "IMouseCameraSelector.h"
#include "DxLib.h"
#include "UIMouseCoordinateConverter.h"
#include "CameraMouseCoordinateConverter.h"
#include "Camera2DComponent.h"
#include "Application.h"

std::shared_ptr<IMouseCoordinateConverter> IMouseCameraSelector::GetCurrentMouseConverter()
{
    int mouseX, mouseY;
    if (auto mouseProv = Application::GetInstance().GetMouseProvider()) {
        mouseProv->GetMousePosition(mouseX, mouseY);
    }
    else {
        GetMousePoint(&mouseX, &mouseY);
    }
    printfDx("Mouse: %d %d\n", mouseX, mouseY);

    std::shared_ptr<Camera2DComponent> selectedCamera = nullptr;

    // renderLayerが最も高いものを選択
    for (auto& camObj : cameras) {
        auto camComp = camObj->GetComponent<Camera2DComponent>();
        if (!camComp) continue;

        int dx = camComp->destX;
        int dy = camComp->destY;
        int dWidth = camComp->destWidth;
        int dHeight = camComp->destHeight;
        printfDx("Camera: (%d, %d) W%d H%d, RenderLayer: %d\n", dx, dy, dWidth, dHeight, camComp->renderLayer);
        if (mouseX >= dx && mouseX <= dx + dWidth &&
            mouseY >= dy && mouseY <= dy + dHeight) {
            if (!selectedCamera || camComp->renderLayer > selectedCamera->renderLayer) {
                selectedCamera = camComp;
            }
        }
    }

    if (selectedCamera) {
        printfDx("[GLOBAL] Target Camera: RenderLayer: %d\n", selectedCamera->renderLayer);
        return std::make_shared<CameraMouseCoordinateConverter>(selectedCamera);
    }
    else {
        return nullptr;
    }
}

std::shared_ptr<IMouseCoordinateConverter> IMouseCameraSelector::GetCurrentMouseConverter(int targetLayer)
{
    int mouseX, mouseY;
    if (auto mouseProv = Application::GetInstance().GetMouseProvider()) {
        mouseProv->GetMousePosition(mouseX, mouseY);
    }
    else {
        GetMousePoint(&mouseX, &mouseY);
    }
    printfDx("Mouse: %d %d\n", mouseX, mouseY);

    std::shared_ptr<Camera2DComponent> selectedCamera = nullptr;

    // 対象レイヤーのカメラのみ
    for (auto& camObj : cameras) {
        if (camObj->GetLayer() != targetLayer) continue;

        auto camComp = camObj->GetComponent<Camera2DComponent>();
        if (!camComp) continue;

        int dx = camComp->destX;
        int dy = camComp->destY;
        int dWidth = camComp->destWidth;
        int dHeight = camComp->destHeight;
        printfDx("Camera (Layer %d): (%d, %d) W%d H%d, RenderLayer: %d\n",
            targetLayer, dx, dy, dWidth, dHeight, camComp->renderLayer);
        if (mouseX >= dx && mouseX <= dx + dWidth &&
            mouseY >= dy && mouseY <= dy + dHeight) {
            if (!selectedCamera || camComp->renderLayer > selectedCamera->renderLayer) {
                selectedCamera = camComp;
            }
        }
    }

    if (selectedCamera) {
        printfDx("Target Camera: RenderLayer: %d\n", selectedCamera->renderLayer);
        return std::make_shared<CameraMouseCoordinateConverter>(selectedCamera);
    }
    else {
        return nullptr;
    }
}
