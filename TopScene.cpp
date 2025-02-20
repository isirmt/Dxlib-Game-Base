#include "TopScene.h"

#include <memory>

#include "AutoDestroyComponent.h"
#include "ButtonComponent.h"
#include "Camera2DComponent.h"
#include "ColliderComponent.h"
#include "DragComponent.h"
#include "DxLib.h"
#include "Point2DComponent.h"
#include "Rect2DComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TransformComponent.h"

void TopScene::Start() {
  auto CreateObject = [](const std::string& name) -> GameObjectPtr {
    return std::make_shared<GameObject>(name);
  };

  // 予め使う分を宣言
  int meiryo20 = ResourceManager::GetInstance().LoadFont("Meiryo", 20, -1);
  int meiryo40 = ResourceManager::GetInstance().LoadFont("Meiryo", 40, -1);

  RegisterRenderTarget(0, 1280, 720);

  // カメラ1 と カメラ2の定義: 浮遊用
  RegisterRenderTarget(1, 500, 500);
  RegisterRenderTarget(2, 500, 500);

  {
    // カメラ: 背景描画用
    GameObjectPtr camera0 = CreateObject("camera0");
    camera0->SetLayer(0);
    camera0->AddComponent<TransformComponent>(0.f, 0.f);
    camera0->AddComponent<Camera2DComponent>(0, 0, 1280, 720, 1280, 720, 0);
    AddObject(camera0);

    // 背景: カメラ0
    GameObjectPtr camera0BackRect = CreateObject("camera0BackRect");
    camera0BackRect->SetLayer(0);
    camera0BackRect->SetOrderInLayer(-100);
    camera0BackRect->AddComponent<TransformComponent>();
    camera0BackRect->AddComponent<Rect2DComponent>(1280.f, 720.f,
                                                   GetColor(239, 241, 243));
    AddObject(camera0BackRect);
  }

  {
    // カメラ1: 浮遊ウインドウのメイン部分
    GameObjectPtr camera1 = CreateObject("camera1");
    camera1->SetLayer(1);
    camera1->AddComponent<TransformComponent>(500.f, 100.f);
    camera1->AddComponent<Camera2DComponent>(0, 0, 500, 500, 500, 500, 1);
    AddObject(camera1);

    // 背景: カメラ1
    GameObjectPtr camera1BackRect = CreateObject("camera1BackRect");
    camera1BackRect->SetLayer(1);
    camera1BackRect->SetOrderInLayer(-100);
    camera1BackRect->AddComponent<TransformComponent>();
    camera1BackRect->AddComponent<Rect2DComponent>(500.f, 500.f,
                                                   GetColor(219, 211, 216));
    AddObject(camera1BackRect);

    // カメラ1のバナー
    GameObjectPtr camera1Banner = CreateObject("camera1Banner");
    camera1Banner->SetLayer(1);
    camera1Banner->SetOrderInLayer(1000);
    camera1Banner->AddComponent<TransformComponent>();
    camera1Banner->AddComponent<Rect2DComponent>(500.f, 40.f,
                                                 GetColor(34, 56, 67));
    AddObject(camera1Banner);
  }

  {
    // カメラ2: 浮遊ウインドウのメイン部分
    GameObjectPtr camera2 = CreateObject("camera2");
    camera2->SetLayer(2);
    camera2->AddComponent<TransformComponent>(700.f, 150.f);
    camera2->AddComponent<Camera2DComponent>(0, 0, 500, 500, 500, 500, 2);
    AddObject(camera2);

    // 背景: カメラ2
    GameObjectPtr camera2BackRect = CreateObject("camera2BackRect");
    camera2BackRect->SetLayer(2);
    camera2BackRect->SetOrderInLayer(-100);
    camera2BackRect->AddComponent<TransformComponent>();
    camera2BackRect->AddComponent<Rect2DComponent>(500.f, 500.f,
                                                   GetColor(216, 203, 199));
    AddObject(camera2BackRect);

    // カメラ2のバナー
    GameObjectPtr camera2Banner = CreateObject("camera2Banner");
    camera2Banner->SetLayer(2);
    camera2Banner->SetOrderInLayer(1000);
    camera2Banner->AddComponent<TransformComponent>();
    camera2Banner->AddComponent<Rect2DComponent>(500.f, 40.f,
                                                 GetColor(25, 35, 26));
    AddObject(camera2Banner);
  }
}

void TopScene::OnButtonClickedMember() {
  int randX = GetRand(1280);
  int randY = GetRand(720);
  int r = GetRand(256);
  int g = GetRand(256);
  int b = GetRand(256);
  int l = GetRand(2);

  // ドラッグ操作可能
  GameObjectPtr randomRectObj = std::make_shared<GameObject>("randomRect");
  randomRectObj->SetLayer(l);
  randomRectObj->SetOrderInLayer(10);
  randomRectObj->AddComponent<TransformComponent>(static_cast<float>(randX),
                                                  static_cast<float>(randY));
  randomRectObj->AddComponent<ColliderComponent>(50.f, 50.f);
  randomRectObj->AddComponent<Rect2DComponent>(50.f, 50.f, GetColor(r, g, b));
  randomRectObj->AddComponent<AutoDestroyComponent>(5.f);
  randomRectObj->AddTag("Object");
  auto dragComp = randomRectObj->AddComponent<DragComponent>();
  dragComp->cameraSelector = cameraSelector;
  // dragComp->ignoreLayerCheck = true;
  this->AddObject(randomRectObj);
}
