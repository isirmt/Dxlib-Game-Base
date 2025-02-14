#pragma once
#include <vector>
#include <list>
#include <memory>
#include "GameObject.h"
#include "IMouseCameraSelector.h"

class Scene : public std::enable_shared_from_this<Scene>
{
	std::list<GameObjectPtr> gameObjects;

protected:
	int offscreenHandle = 0;
	std::shared_ptr<IMouseCameraSelector> cameraSelector;

public:
	Scene() : cameraSelector(std::make_shared<IMouseCameraSelector>()) {};
	virtual ~Scene();

	virtual void Update();
	virtual void Render();

	virtual void Start() = 0;
	virtual void Reset();

	void AddObject(GameObjectPtr obj);

private:
	void ProcessPending();

};

