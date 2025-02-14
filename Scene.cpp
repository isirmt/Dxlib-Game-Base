#include "Scene.h"
#include "DxLib.h"
#include "Camera2DComponent.h"
#include <algorithm>
#include <iterator>

Scene::~Scene()
{
	DeleteGraph(offscreenHandle);
}

void Scene::Update()
{
	std::list<GameObjectPtr> objects;
	std::copy_if(
		gameObjects.begin(), gameObjects.end(), std::back_inserter(objects),
		[](const GameObjectPtr& obj) {
			return obj->HasTag("Object");
		}
	);

	for (auto& obj : objects) {
		obj->Update();
	}

	std::list<GameObjectPtr> cameras;
	std::copy_if(
		gameObjects.begin(), gameObjects.end(), std::back_inserter(cameras),
		[](const GameObjectPtr& obj) {
			return obj->HasTag("Camera");
		}
	);

	for (auto& camera : cameras) {
		camera->Update();
	}

	std::list<GameObjectPtr> uiObjects;
	std::copy_if(
		gameObjects.begin(), gameObjects.end(), std::back_inserter(uiObjects),
		[](const GameObjectPtr& obj) {
			return obj->HasTag("UI");
		}
	);

	for (auto& ui : uiObjects) {
		ui->Update();
	}

	ProcessPending();
}

void Scene::Render()
{
	SetDrawScreen(offscreenHandle);
	ClearDrawScreen();

	std::list<GameObjectPtr> objects;
	std::copy_if(
		gameObjects.begin(), gameObjects.end(), std::back_inserter(objects),
		[](const GameObjectPtr& obj) {
			return obj->HasTag("Object");
		}
	);

	for (auto& obj : objects) {
		obj->Render();
	}

	SetDrawScreen(DX_SCREEN_BACK);

	std::list<GameObjectPtr> cameras;
	std::copy_if(
		gameObjects.begin(), gameObjects.end(), std::back_inserter(cameras),
		[](const GameObjectPtr& obj) {
			return obj->HasTag("Camera");
		}
	);

	for (auto& camera : cameras) {
		auto camComp = camera->GetComponent<Camera2DComponent>();
		if (camComp) {
			camComp->Render(offscreenHandle);
		}
	}

	std::list<GameObjectPtr> uiObjects;
	std::copy_if(
		gameObjects.begin(), gameObjects.end(), std::back_inserter(uiObjects),
		[](const GameObjectPtr& obj) {
			return obj->HasTag("UI");
		}
	);

	for (auto& ui : uiObjects) {
		ui->Render();
	}
}

void Scene::Reset()
{
	gameObjects.clear();
	Start();
}

void Scene::AddObject(GameObjectPtr obj)
{
	gameObjects.push_back(obj);
}

void Scene::ProcessPending()
{
	gameObjects.remove_if([](const GameObjectPtr& obj) { return obj->ShouldBeDestroyed(); });
}
