#pragma once
#include <memory>

class Application
{
private:
	static std::unique_ptr<Application> pinstance_;

	bool running;
	bool requestedReseting;
	//std::shared_ptr<Scene> currentScene_;

protected:

	Application();

	void Update();
	void Render();

public:

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	static Application& GetInstance();

	void Run();
};
