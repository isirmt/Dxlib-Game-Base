#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "Application.h"
#include "DxLib.h"
#include "TopScene.h"
#include "Time.h"
#include "MousePicker.h"

Application::Application() : running(true)
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
	sceneManager = std::make_shared<SceneManager>();

	ChangeScene(std::make_shared<TopScene>());
}

void Application::ChangeScene(std::shared_ptr<Scene> newScene)
{
	newScene->SetCameraSelector(cameraSelector);
	newScene->SetMouseProvider(mouseProvider);
	sceneManager->ChangeScene(newScene);
}

void Application::AdditiveScene(std::shared_ptr<Scene> additiveScene)
{
	additiveScene->SetCameraSelector(cameraSelector);
	additiveScene->SetMouseProvider(mouseProvider);
	sceneManager->AdditiveScene(additiveScene);
}

void Application::UnloadScene(std::shared_ptr<Scene> scene)
{
	sceneManager->UnloadScene(scene);
}

void Application::Update()
{
	Time::GetInstance().Update();
	sceneManager->Update();
}

void Application::Render()
{
	sceneManager->Render();
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

	MousePicker picker;
	return picker.GetTopGameObjectAtPoint(sceneManager->GetScenes(), mouseScreenX, mouseScreenY, cameraSelector);
}

void Application::Run()
{
	while (running && !ScreenFlip() && !ProcessMessage() && !clsDx()) {
		Update();
		Render();
	}
	exit(EXIT_SUCCESS);
}
