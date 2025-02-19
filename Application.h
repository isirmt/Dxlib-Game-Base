#pragma once
#include <memory>
#include <vector>
#include "Scene.h"
#include "Singleton.h"
#include "WindowManager.h"

class Application : public Singleton<Application>
{
	friend class Singleton<Application>;
	bool running;
	bool requestedReseting;
	std::vector<std::shared_ptr<Scene>> scenes_;
	std::shared_ptr<WindowManager> windowManager;
	std::shared_ptr<IMouseCameraSelector> cameraSelector;
	std::shared_ptr<IMouseProvider> mouseProvider;

protected:

	Application();

	void Update();
	void Render();

public:
	void ChangeScene(std::shared_ptr<Scene> newScene);

	void AdditiveScene(std::shared_ptr<Scene> additiveScene);

	void UnloadScene(std::shared_ptr<Scene> scene);

	std::shared_ptr<IMouseProvider> GetMouseProvider() const {
		return mouseProvider;
	}

	std::shared_ptr<GameObject> GetTopGameObjectAtPoint();

	void Run();
};
