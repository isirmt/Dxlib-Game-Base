#pragma once
#include <vector>
#include <list>
#include <memory>
#include "GameObject.h"
#include "IMouseCameraSelector.h"
#include "RenderTarget.h"
#include <unordered_map>

class Scene : public std::enable_shared_from_this<Scene>
{
protected:
	std::list<GameObjectPtr> gameObjects;
	int offscreenHandle = 0;
	std::shared_ptr<IMouseCameraSelector> cameraSelector;
	std::unordered_map<int, std::shared_ptr<RenderTarget>> renderTargets;

	bool isAdditive = false;

public:
	Scene() : cameraSelector(std::make_shared<IMouseCameraSelector>()) {};
	virtual ~Scene();

	virtual void Update();
	virtual void Render();

	virtual void Start() = 0;
	virtual void Reset();

	void AddObject(GameObjectPtr obj);

	void RegisterRenderTarget(int layer, int width, int height);

	void SetAdditive(bool additive) { isAdditive = additive; }
	bool IsAdditive() const { return isAdditive; }

private:
	void ProcessPending();

};

