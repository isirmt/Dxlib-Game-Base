#include <iostream>
#include <stdlib.h>
#include "Application.h"
#include "DxLib.h"
#include "TopScene.h"

Application::Application() : running(true), requestedReseting(false)
{
	SetGraphMode(1280, 720, 32);
	SetWindowSize(1280, 720);
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
	{
		exit(EXIT_FAILURE);
	}
	
	ChangeScene(std::make_shared<TopScene>());
}

Application& Application::GetInstance()
{
	static Application instance;

	return instance;
}

void Application::ChangeScene(std::shared_ptr<Scene> newScene)
{
	currentScene_ = std::move(newScene);
	currentScene_->Start();
}

void Application::Update()
{
	if (currentScene_) {
		currentScene_->Update();

		if (requestedReseting) {
			requestedReseting = false;
			currentScene_->Reset();
		}
	}
}

void Application::Render()
{
	if (currentScene_) {
		currentScene_->Render();
	}
}

void Application::Run()
{
	while (running && !ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !clsDx()) {
		SetDrawScreen(DX_SCREEN_BACK);
		Update();
		Render();
	}
	exit(EXIT_SUCCESS);
}
