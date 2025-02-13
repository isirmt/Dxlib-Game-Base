#pragma once
#include <vector>
#include <list>
#include <memory>
#include "GameObject.h"
#include "IMouseCameraSelector.h"

class Scene : public std::enable_shared_from_this<Scene>
{
	std::list<GameObjectPtr> objects;
	std::vector<GameObjectPtr> cameras;
	std::vector<GameObjectPtr> uiObjects;

	std::vector<GameObjectPtr> pendingAddObjects;
	std::vector<GameObjectPtr> pendingAddCameras;
	std::vector<GameObjectPtr> pendingAddUIObjects;

	std::vector<GameObjectPtr> pendingRemoveObjects;
	std::vector<GameObjectPtr> pendingRemoveCameras;
	std::vector<GameObjectPtr> pendingRemoveUIObjects;

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
	void AddCamera(GameObjectPtr obj);
	void AddUIObject(GameObjectPtr obj);

	void DeleteObject(GameObjectPtr obj);
	void DeleteCamera(GameObjectPtr obj);
	void DeleteUIObject(GameObjectPtr obj);

private:
	void ProcessPending();

};

