#pragma once
#include <memory>
#include "Scene.h"

class Application
{
private:
	bool running;
	bool requestedReseting;
	std::shared_ptr<Scene> currentScene_;

protected:

	Application();

	void Update();
	void Render();

public:

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	static Application& GetInstance();

	void ChangeScene(std::shared_ptr<Scene> newScene);

	void Run();
};
