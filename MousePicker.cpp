#include "MousePicker.h"

std::shared_ptr<GameObject> MousePicker::GetTopGameObjectAtPoint(const std::vector<std::shared_ptr<Scene>>& scenes, int mouseScreenX, int mouseScreenY, const std::shared_ptr<IMouseCameraSelector>& cameraSelector)
{
    struct Clickable {
        std::shared_ptr<GameObject> obj;
        int effectiveLayer;
        int order;
        std::shared_ptr<IMouseCoordinateConverter> converter;
    };

    std::vector<Clickable> clickables;

    for (const auto& scene : scenes) {
        for (const auto& obj : scene->GetGameObjects()) {
            if (!obj->IsActive() || !obj->IsVisible()) continue;
            auto collider = obj->GetComponent<ColliderComponent>();
            if (!collider) continue;

            Clickable c;
            c.obj = obj;
            c.order = obj->GetOrderInLayer();

            if (obj->HasTag("UI")) {
                c.effectiveLayer = obj->GetLayer();
                c.converter = std::make_shared<UIMouseCoordinateConverter>();
            }
            else {
                bool foundCam = false;
                for (const auto& camObj : cameraSelector->cameras) {
                    if (camObj->GetLayer() != obj->GetLayer()) continue;
                    auto camComp = camObj->GetComponent<Camera2DComponent>();
                    if (!camComp) continue;
                    if (mouseScreenX >= camComp->destX &&
                        mouseScreenX <= camComp->destX + camComp->destWidth &&
                        mouseScreenY >= camComp->destY &&
                        mouseScreenY <= camComp->destY + camComp->destHeight)
                    {
                        c.effectiveLayer = camComp->renderLayer;
                        c.converter = cameraSelector->GetCurrentMouseConverter();
                        foundCam = true;
                        break;
                    }
                }
                if (!foundCam) continue;
            }
            clickables.push_back(c);
        }
    }

    std::sort(clickables.begin(), clickables.end(), [](const Clickable& a, const Clickable& b) {
        if (a.effectiveLayer == b.effectiveLayer)
            return a.order > b.order;
        return a.effectiveLayer > b.effectiveLayer;
        });

    int convertedX, convertedY;
    for (auto& c : clickables) {
        if (!c.converter) continue;
        c.converter->Convert(mouseScreenX, mouseScreenY, convertedX, convertedY);
        if (c.obj->GetComponent<ColliderComponent>()->Contains(static_cast<float>(convertedX), static_cast<float>(convertedY))) {
            return c.obj;
        }
    }
    return nullptr;
}
