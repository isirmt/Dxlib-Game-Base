#pragma once
#include <vector>
#include "GameObject.h"

class Scene
{
	std::vector<GameObjectPtr> objects;
	std::vector<GameObjectPtr> cameras;
	std::vector<GameObjectPtr> uiObjects;

protected:
	int offscreenHandle = 0;

public:
	Scene() = default;
	virtual ~Scene() {}

	virtual void Update();
	virtual void Render();

	virtual void Start() = 0;
	virtual void Reset();

	void AddObject(GameObjectPtr obj);
	void AddCamera(GameObjectPtr obj);
	void AddUIObject(GameObjectPtr obj);
};

