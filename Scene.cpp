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
    // ���C���[�P�ʂŔ�UI�I�u�W�F�N�g��`��
    for (auto& [layer, renderTarget] : renderTargets)
    {
        SetDrawScreen(renderTarget->handle);
        ClearDrawScreen();

        for (auto& obj : gameObjects)
        {
            if (!obj->HasTag("UI") && obj->GetLayer() == layer)
            {
                obj->Render();
            }
        }
    }

    // DX_SCREEN_BACK�Ƀ����_�[�^�[�Q�b�g���J�����z���ɕ`��
    SetDrawScreen(DX_SCREEN_BACK);
    ClearDrawScreen();

    // �J�����I�u�W�F�N�g�̑I��
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
                camComp->Render(renderTargets[layer]->handle);
            }
        }
    }

    // UI�͒��ڕ`��
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

void Scene::RegisterRenderTarget(int layer, int width, int height)
{
	renderTargets[layer] = std::make_shared<RenderTarget>(layer, width, height);
}

void Scene::ProcessPending()
{
	gameObjects.remove_if([](const GameObjectPtr& obj) { return obj->ShouldBeDestroyed(); });
}
