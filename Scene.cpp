#include "Scene.h"

void Scene::Update()
{
	for (auto& obj : objects) {
		obj->Update();
	}
}

void Scene::Render()
{
	for (auto& obj : objects) {
		obj->Render();
	}
}

void Scene::Reset()
{
	objects.clear();
	Start();
}

void Scene::AddObject(std::shared_ptr<GameObject> obj)
{
	objects.push_back(obj);
}
