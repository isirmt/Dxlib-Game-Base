#include <iostream>
#include <stdlib.h>
#include "Application.h"
#include "DxLib.h"

std::unique_ptr<Application> Application::pinstance_ = nullptr;

Application::Application() : running(true), requestedReseting(false)
{
	if (DxLib_Init() == -1)
	{
		exit(EXIT_FAILURE);
	}
	std::cout << "Initialized" << std::endl;
}

Application& Application::GetInstance()
{
	if (!pinstance_) {
		pinstance_ = std::unique_ptr<Application>(
			new Application());
	}

	return *pinstance_;
}

void Application::Update()
{
}

void Application::Render()
{
}

void Application::Run()
{
	//while (running)
	//{
	//	Update();
	//	Render();
	//}
	DrawPixel(320, 240, GetColor(255, 255, 255));
	WaitKey();
	DxLib_End();
	exit(EXIT_SUCCESS);
}
