#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "Application.h"
#include "DxLib.h"
#include "TopScene.h"
#include "ColliderComponent.h"
#include "IMouseCoordinateConverter.h"
#include "GameObject.h"
#include "Time.h"
#include "UIMouseCoordinateConverter.h"
#include "CameraMouseCoordinateConverter.h"

Application::Application() : running(true), requestedReseting(false)
{
	SetGraphMode(1280, 720, 32);
	SetWindowSize(1280, 720);
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
	{
		exit(EXIT_FAILURE);
	}

	windowManager = std::make_shared<WindowManager>(1280, 720);
	cameraSelector = std::make_shared<IMouseCameraSelector>();
	mouseProvider = std::make_shared<DxMouseProvider>(windowManager);

	ChangeScene(std::make_shared<TopScene>());
}

void Application::ChangeScene(std::shared_ptr<Scene> newScene)
{
	scenes_.clear();
	newScene->SetAdditive(false);
	newScene->SetCameraSelector(cameraSelector);
	newScene->SetMouseProvider(mouseProvider);
	scenes_.push_back(newScene);
	newScene->Start();
}

void Application::AdditiveScene(std::shared_ptr<Scene> additiveScene)
{
	additiveScene->SetAdditive(true); // クリアは行わない
	additiveScene->SetCameraSelector(cameraSelector);
	additiveScene->SetMouseProvider(mouseProvider);
	scenes_.push_back(additiveScene);
	additiveScene->Start();
}

void Application::UnloadScene(std::shared_ptr<Scene> scene)
{
	scenes_.erase(std::remove(scenes_.begin(), scenes_.end(), scene), scenes_.end());
}

void Application::Update()
{
	Time& time = Time::GetInstance();
	time.Update();
	for (auto& scene : scenes_)
	{
		scene->Update();
		// ベースシーンに対してリセット要求があるか
		if (!scene->IsAdditive() && requestedReseting)
		{
			requestedReseting = false;
			scene->Reset();
		}
	}
}

void Application::Render()
{
	for (auto& scene : scenes_)
	{
		scene->Render();
	}
}

std::shared_ptr<GameObject> Application::GetTopGameObjectAtPoint()
{
    int mouseScreenX, mouseScreenY;
    if (mouseProvider) {
        mouseProvider->GetMousePosition(mouseScreenX, mouseScreenY);
    }
    else {
        GetMousePoint(&mouseScreenX, &mouseScreenY);
    }

    // 一時的にまとめる構造体
    struct Clickable {
        std::shared_ptr<GameObject> obj;
        int effectiveLayer;
        int order;
        std::shared_ptr<IMouseCoordinateConverter> converter;
    };

    std::vector<Clickable> clickables;

    // 全シーンの全オブジェクトを対象
    for (auto& scene : scenes_) {
        for (auto& obj : scene->GetGameObjects()) {
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
                for (auto& camObj : cameraSelector->cameras) {
                    if (camObj->GetLayer() != obj->GetLayer())
                        continue;
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
                if (!foundCam) {
                    continue;
                }
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

void Application::Run()
{
	while (running && !ScreenFlip() && !ProcessMessage() && !clsDx()) {
		Update();
		Render();
	}
	exit(EXIT_SUCCESS);
}
