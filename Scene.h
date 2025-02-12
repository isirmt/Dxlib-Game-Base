#pragma once
#include <vector>
#include "GameObject.h"

class Scene
{
	std::vector<std::shared_ptr<GameObject>> objects;

public:
	Scene() = default;
	virtual ~Scene() {}

	virtual void Update();
	virtual void Render();

	virtual void Start() = 0;
	virtual void Reset();

	void AddObject(std::shared_ptr<GameObject> obj);
};

