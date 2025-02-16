#pragma once
#include <memory>
#include <vector>
#include "Scene.h"

class Application
{
private:
	bool running;
	bool requestedReseting;
	std::vector<std::shared_ptr<Scene>> scenes_;

protected:

	Application();

	void Update();
	void Render();

public:

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	static Application& GetInstance();

	void ChangeScene(std::shared_ptr<Scene> newScene);

	void AdditiveScene(std::shared_ptr<Scene> additiveScene);

	void UnloadScene(std::shared_ptr<Scene> scene);

	void Run();
};
