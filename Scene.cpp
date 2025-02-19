#include "Scene.h"
#include "DxLib.h"
#include "Camera2DComponent.h"
#include <algorithm>
#include <iterator>
#include <functional>

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
	// ���C���[�P�ʂŔ�UI�I�u�W�F�N�g��`��
	for (auto& [layer, renderTarget] : renderTargets) {
		SetDrawScreen(renderTarget->handle);
		ClearDrawScreen();

		std::vector<GameObjectPtr> layerObjects;
		for (auto& obj : gameObjects) {
			if (!obj->HasTag("UI") && obj->GetLayer() == layer) {
				layerObjects.push_back(obj);
			}
		}

		// orderInLayer�Ń\�[�g(�傫���قǏ��)
		std::sort(
			layerObjects.begin(), layerObjects.end(),
			[](const GameObjectPtr& a, const GameObjectPtr& b) {
				return a->GetOrderInLayer() < b->GetOrderInLayer();
			}
		);

		for (auto& obj : layerObjects) {
			obj->Render();
		}
	}

	// DX_SCREEN_BACK�Ƀ����_�[�^�[�Q�b�g���J�����z���ɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	if (!isAdditive) {
		ClearDrawScreen();
	}

	// �����_�[�\����(�����̕ێ�)

	struct RenderCommand {
		int order;
		std::function<void()> command;
	};
	std::vector<RenderCommand> renderQueue;

	// �J�����ɂ��`��

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
			int layer = camComp->renderLayer;
			if (renderTargets.find(layer) != renderTargets.end()) {
				int order = camera->GetOrderInLayer();
				int rtHandle = renderTargets[layer]->handle;
				renderQueue.push_back({
					order,
					[camComp, rtHandle]() {
						camComp->Render(rtHandle);
					}
					}
				);
			}
		}
	}

	// UI�̕`��

	std::vector<GameObjectPtr> uiObjects;
	for (auto& obj : gameObjects) {
		if (obj->HasTag("UI")) {
			uiObjects.push_back(obj);
		}
	}

	std::sort(
		uiObjects.begin(), uiObjects.end(),
		[](const GameObjectPtr& a, const GameObjectPtr& b) {
			return a->GetOrderInLayer() < b->GetOrderInLayer();
		}
	);

	for (auto& ui : uiObjects) {
		int order = ui->GetOrderInLayer();
		renderQueue.push_back({
			order,
			[ui]() {
				ui->Render();
			}
			}
		);
	}

	// �L���[���\�[�g
	std::sort(
		renderQueue.begin(), renderQueue.end(),
		[](const RenderCommand& a, const RenderCommand& b) {
			return a.order < b.order;
		}
	);

	for (auto& cmd : renderQueue) {
		cmd.command();
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

void Scene::RegisterRenderTarget(int layer, int width, int height)
{
	renderTargets[layer] = std::make_shared<RenderTarget>(layer, width, height);
}

void Scene::ProcessPending()
{
	gameObjects.remove_if([](const GameObjectPtr& obj) { return obj->ShouldBeDestroyed(); });
}
