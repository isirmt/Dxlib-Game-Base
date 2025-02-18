#pragma once
#include <memory>
#include <vector>
#include "Scene.h"
#include "Singleton.h"

class Application : public Singleton<Application>
{
	friend class Singleton<Application>;
	bool running;
	bool requestedReseting;
	std::vector<std::shared_ptr<Scene>> scenes_;

protected:

	Application();

	void Update();
	void Render();

public:
	void ChangeScene(std::shared_ptr<Scene> newScene);

	void AdditiveScene(std::shared_ptr<Scene> additiveScene);

	void UnloadScene(std::shared_ptr<Scene> scene);

	void Run();
};
