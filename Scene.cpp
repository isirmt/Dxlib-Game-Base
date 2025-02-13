#include "Scene.h"
#include "DxLib.h"
#include "Camera2DComponent.h"

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
	Start();
}

void Scene::AddObject(GameObjectPtr obj)
{
	objects.push_back(obj);
}

void Scene::AddCamera(GameObjectPtr obj)
{
	cameras.push_back(obj);
}

void Scene::AddUIObject(GameObjectPtr obj)
{
	uiObjects.push_back(obj);
}
