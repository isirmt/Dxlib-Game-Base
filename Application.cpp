#include <iostream>
#include <stdlib.h>
#include "Application.h"
#include "DxLib.h"
#include "TopScene.h"
#include "ColliderComponent.h"
#include "IMouseCoordinateConverter.h"
#include "GameObject.h"
#include "Time.h"
#include "UIMouseCoordinateConverter.h"

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
	std::shared_ptr<GameObject> topObject = nullptr;
	// 仮の最小値
	int topLayer = -100000;
	int topOrder = -100000;

	int mouseScreenX, mouseScreenY;
	if (mouseProvider) {
		mouseProvider->GetMousePosition(mouseScreenX, mouseScreenY);
	}
	else {
		GetMousePoint(&mouseScreenX, &mouseScreenY);
	}

	for (auto& scene : scenes_)
	{
		for (auto& obj : scene->GetGameObjects())
		{
			if (!obj->IsActive() || !obj->IsVisible()) continue;

			auto collider = obj->GetComponent<ColliderComponent>();
			if (!collider) continue;

			std::shared_ptr<IMouseCoordinateConverter> converter;
			if (cameraSelector) {
				if (!obj->HasTag("UI") && !obj->HasTag("Camera")) {
					converter = cameraSelector->GetCurrentMouseConverter(obj->GetLayer());;
				}
				else {
					converter = std::make_shared<UIMouseCoordinateConverter>();
				}
			}
			else {
				OutputDebugString("Application::GetTopGameObjectAtPoint() has no cameraSelector\n");
			}

			if (!converter) continue;

			int convertedX, convertedY;
			converter->Convert(mouseScreenX, mouseScreenY, convertedX, convertedY);

			if (collider->Contains(static_cast<float>(convertedX), static_cast<float>(convertedY)))
			{
				int objLayer = obj->GetLayer();
				int objOrder = obj->GetOrderInLayer();

				if (objLayer > topLayer || (objLayer == topLayer && objOrder > topOrder))
				{
					topLayer = objLayer;
					topOrder = objOrder;
					topObject = obj;
				}
			}
		}
	}
	return topObject;
}

void Application::Run()
{
	while (running && !ScreenFlip() && !ProcessMessage() && !clsDx()) {
		Update();
		Render();
	}
	exit(EXIT_SUCCESS);
}
