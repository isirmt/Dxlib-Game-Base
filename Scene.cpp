#include "Scene.h"
#include "DxLib.h"
#include "Camera2DComponent.h"

Scene::~Scene()
{
	DeleteGraph(offscreenHandle);
}

void Scene::Update()
{
	for (auto& obj : objects) {
		obj->Update();
	}

	for (auto& camera : cameras) {
		camera->Update();
	}

	for (auto& ui : uiObjects) {
		ui->Update();
	}

	ProcessPending();
}

void Scene::Render()
{
	SetDrawScreen(offscreenHandle);
	ClearDrawScreen();

	for (auto& obj : objects) {
		obj->Render();
	}

	SetDrawScreen(DX_SCREEN_BACK);

	for (auto& camera : cameras) {
		auto camComp = camera->GetComponent<Camera2DComponent>();
		if (camComp) {
			camComp->Render(offscreenHandle);
		}
	}

	for (auto& ui : uiObjects) {
		ui->Render();
	}
}

void Scene::Reset()
{
	objects.clear();
	cameras.clear();
	uiObjects.clear();
	pendingAddObjects.clear();
	pendingAddCameras.clear();
	pendingAddUIObjects.clear();
	pendingRemoveObjects.clear();
	pendingRemoveCameras.clear();
	pendingRemoveUIObjects.clear();
	Start();
}

void Scene::AddObject(GameObjectPtr obj)
{
	pendingAddObjects.push_back(obj);
}

void Scene::AddCamera(GameObjectPtr obj)
{
	pendingAddCameras.push_back(obj);
}

void Scene::AddUIObject(GameObjectPtr obj)
{
	pendingAddUIObjects.push_back(obj);
}

void Scene::DeleteObject(GameObjectPtr obj)
{
	pendingRemoveObjects.push_back(obj);
}

void Scene::DeleteCamera(GameObjectPtr obj)
{
	pendingRemoveCameras.push_back(obj);
}

void Scene::DeleteUIObject(GameObjectPtr obj)
{
	pendingRemoveUIObjects.push_back(obj);
}

void Scene::ProcessPending()
{
	if (!pendingRemoveObjects.empty()) {
		objects.erase(
			std::remove_if(
				objects.begin(), objects.end(),
				[this](const GameObjectPtr& obj) {
					return std::find(pendingRemoveObjects.begin(), pendingRemoveObjects.end(), obj) != pendingRemoveObjects.end();
				}
			),
			objects.end()
		);
		pendingRemoveObjects.clear();
	}
	if (!pendingRemoveCameras.empty()) {
		cameras.erase(
			std::remove_if(
				cameras.begin(), cameras.end(),
				[this](const GameObjectPtr& obj) {
					return std::find(pendingRemoveCameras.begin(), pendingRemoveCameras.end(), obj) != pendingRemoveCameras.end();
				}
			),
			cameras.end()
		);
		pendingRemoveCameras.clear();
	}
	if (!pendingRemoveUIObjects.empty()) {
		uiObjects.erase(
			std::remove_if(
				uiObjects.begin(), uiObjects.end(),
				[this](const GameObjectPtr& obj) {
					return std::find(pendingRemoveUIObjects.begin(), pendingRemoveUIObjects.end(), obj) != pendingRemoveUIObjects.end();
				}
			),
			uiObjects.end()
		);
		pendingRemoveUIObjects.clear();
	}

	if (!pendingAddObjects.empty()) {
		objects.insert(objects.end(), pendingAddObjects.begin(), pendingAddObjects.end());
		pendingAddObjects.clear();
	}
	if (!pendingAddCameras.empty()) {
		cameras.insert(cameras.end(), pendingAddCameras.begin(), pendingAddCameras.end());
		cameraSelector->cameras.insert(cameraSelector->cameras.end(), pendingAddCameras.begin(), pendingAddCameras.end());
		pendingAddCameras.clear();
	}
	if (!pendingAddUIObjects.empty()) {
		uiObjects.insert(uiObjects.end(), pendingAddUIObjects.begin(), pendingAddUIObjects.end());
		pendingAddUIObjects.clear();
	}
}
