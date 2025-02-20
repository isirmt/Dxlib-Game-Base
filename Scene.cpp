#include "Scene.h"

#include <algorithm>
#include <functional>
#include <iterator>

#include "Camera2DComponent.h"
#include "DxLib.h"

void Scene::Update() {
  for (auto& obj : gameObjects) {
    obj->Update();
  }
  ProcessPending();
}

void Scene::Render() {
  for (auto& [layer, renderTarget] : renderTargets) {
    SetDrawScreen(renderTarget->handle);
    ClearDrawScreen();

    std::vector<GameObjectPtr> layerObjects;
    for (auto& obj : gameObjects) {
      // Camera2DComponentを持たないものを対象
      if (obj->GetLayer() == layer && !obj->GetComponent<Camera2DComponent>()) {
        layerObjects.push_back(obj);
      }
    }

    std::sort(layerObjects.begin(), layerObjects.end(),
              [](const GameObjectPtr& a, const GameObjectPtr& b) {
                return a->GetOrderInLayer() < b->GetOrderInLayer();
              });

    for (auto& obj : layerObjects) {
      obj->Render();
    }
  }

  // Camera2DComponentを持つオブジェクト
  struct RenderCommand {
    int order;
    std::function<void()> command;
  };
  std::vector<RenderCommand> renderQueue;

  std::vector<GameObjectPtr> cameraObjects;
  for (auto& obj : gameObjects) {
    if (obj->GetComponent<Camera2DComponent>()) {
      cameraObjects.push_back(obj);
    }
  }

  for (auto& camObj : cameraObjects) {
    auto camComp = camObj->GetComponent<Camera2DComponent>();
    if (camComp) {
      int layer = camComp->renderLayer;
      if (renderTargets.find(layer) != renderTargets.end()) {
        int order = camObj->GetOrderInLayer();
        int rtHandle = renderTargets[layer]->handle;
        renderQueue.push_back(
            {order, [camComp, rtHandle]() { camComp->Render(rtHandle); }});
      }
    }
  }

  // 描画順にソート
  std::sort(renderQueue.begin(), renderQueue.end(),
            [](const RenderCommand& a, const RenderCommand& b) {
              return a.order < b.order;
            });

  SetDrawScreen(DX_SCREEN_BACK);
  if (!isAdditive) {
    ClearDrawScreen();
  }
  for (auto& cmd : renderQueue) {
    cmd.command();
  }
}

void Scene::Reset() {
  gameObjects.clear();
  Start();
}

void Scene::AddObject(GameObjectPtr obj) { gameObjects.push_back(obj); }

void Scene::RegisterRenderTarget(int layer, int width, int height) {
  renderTargets[layer] = std::make_shared<RenderTarget>(layer, width, height);
}

void Scene::ProcessPending() {
  gameObjects.remove_if(
      [](const GameObjectPtr& obj) { return obj->ShouldBeDestroyed(); });
}
