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
  int meiryo30 = ResourceManager::GetInstance().LoadFont("Meiryo", 30, -1);

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
    cameraSelector->cameras.push_back(camera0);

    // 背景: カメラ0
    GameObjectPtr camera0BackRect = CreateObject("camera0BackRect");
    camera0BackRect->SetLayer(0);
    camera0BackRect->SetOrderInLayer(-100);
    camera0BackRect->AddComponent<TransformComponent>();
    camera0BackRect->AddComponent<Rect2DComponent>(1280.f, 720.f,
                                                   GetColor(239, 241, 243));
    AddObject(camera0BackRect);

    GameObjectPtr rectSpawningButton0 = CreateObject("rectSpawningButton0");
    rectSpawningButton0->SetLayer(0);
    rectSpawningButton0->SetOrderInLayer(5);
    rectSpawningButton0->AddComponent<TransformComponent>(100.f, 400.f);
    auto rectSpawningButton0DragComp =
        rectSpawningButton0->AddComponent<DragComponent>();
    rectSpawningButton0->AddComponent<ColliderComponent>(250.f, 150.f);
    rectSpawningButton0->AddComponent<Rect2DComponent>(250.f, 150.f,
                                                       GetColor(75, 136, 162));
    rectSpawningButton0->AddComponent<TextComponent>(
        "[ドラッグ可能]\nレイヤー０オブジェクト", meiryo20,
        GetColor(10, 10, 10), 250, 45);

    rectSpawningButton0DragComp->cameraSelector = cameraSelector;
    AddObject(rectSpawningButton0);
  }

  {
    // カメラ1: 浮遊ウインドウのメイン部分
    GameObjectPtr camera1 = CreateObject("camera1");
    camera1->SetLayer(1);
    camera1->AddComponent<TransformComponent>(500.f, 100.f);
    camera1->AddComponent<Camera2DComponent>(0, 0, 500, 500, 500, 500, 1);
    AddObject(camera1);
    cameraSelector->cameras.push_back(camera1);

    // 背景: カメラ1
    GameObjectPtr camera1BackRect = CreateObject("camera1BackRect");
    camera1BackRect->SetLayer(1);
    camera1BackRect->SetOrderInLayer(-100);
    camera1BackRect->AddComponent<TransformComponent>();
    camera1BackRect->AddComponent<ColliderComponent>(500.f, 500.f);
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

    GameObjectPtr rectSpawningButton1 = CreateObject("rectSpawningButton1");
    rectSpawningButton1->SetLayer(1);
    rectSpawningButton1->SetOrderInLayer(5);
    rectSpawningButton1->AddComponent<TransformComponent>(100.f, 100.f);
    auto rectSpawningButton1DragComp =
        rectSpawningButton1->AddComponent<DragComponent>();
    rectSpawningButton1->AddComponent<ColliderComponent>(250.f, 150.f);
    rectSpawningButton1->AddComponent<Rect2DComponent>(250.f, 150.f,
                                                       GetColor(75, 136, 162));
    rectSpawningButton1->AddComponent<TextComponent>(
        "[ドラッグ可能]\nレイヤー１オブジェクト", meiryo20,
        GetColor(10, 10, 10), 250, 45);

    rectSpawningButton1DragComp->cameraSelector = cameraSelector;
    AddObject(rectSpawningButton1);
  }

  {
    // カメラ2: 浮遊ウインドウのメイン部分
    GameObjectPtr camera2 = CreateObject("camera2");
    camera2->SetLayer(2);
    camera2->AddComponent<TransformComponent>(700.f, 150.f);
    camera2->AddComponent<Camera2DComponent>(0, 0, 500, 500, 500, 500, 2);
    AddObject(camera2);
    cameraSelector->cameras.push_back(camera2);

    // 背景: カメラ2
    GameObjectPtr camera2BackRect = CreateObject("camera2BackRect");
    camera2BackRect->SetLayer(2);
    camera2BackRect->SetOrderInLayer(-100);
    camera2BackRect->AddComponent<TransformComponent>();
    camera2BackRect->AddComponent<ColliderComponent>(500.f, 500.f);
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

    GameObjectPtr rectSpawningButton2 = CreateObject("rectSpawningButton2");
    rectSpawningButton2->SetLayer(2);
    rectSpawningButton2->SetOrderInLayer(5);
    rectSpawningButton2->AddComponent<TransformComponent>(100.f, 100.f);
    auto rectSpawningButton2DragComp =
        rectSpawningButton2->AddComponent<DragComponent>();
    rectSpawningButton2->AddComponent<ColliderComponent>(250.f, 200.f);
    rectSpawningButton2->AddComponent<Rect2DComponent>(250.f, 200.f,
                                                       GetColor(187, 10, 33));
    rectSpawningButton2->AddComponent<TextComponent>(
        "[ドラッグ可能]\n[離トリガー]\nレイヤー２オブジェクト", meiryo30,
        GetColor(10, 10, 10), 250, 45);
    auto rectSpawningButton2ButtonComp =
        rectSpawningButton2->AddComponent<ButtonComponent>();

    rectSpawningButton2DragComp->cameraSelector = cameraSelector;
    rectSpawningButton2ButtonComp->cameraSelector = cameraSelector;
    rectSpawningButton2ButtonComp->AddOnClickListener(
        std::bind(&TopScene::OnButtonClickedMember, this));
    AddObject(rectSpawningButton2);
  }
}

void TopScene::OnButtonClickedMember() {
  int randX = GetRand(500);
  int randY = GetRand(500);
  int r = GetRand(256);
  int g = GetRand(256);
  int b = GetRand(256);
  int l = GetRand(3); // == 3のみ表示されない
  int oIL = GetRand(10);

  GameObjectPtr randomRect = std::make_shared<GameObject>("randomRect");
  randomRect->SetLayer(l);
  randomRect->SetOrderInLayer(oIL);
  randomRect->AddComponent<TransformComponent>(static_cast<float>(randX),
                                                  static_cast<float>(randY));
  randomRect->AddComponent<ColliderComponent>(50.f, 50.f);
  randomRect->AddComponent<Rect2DComponent>(50.f, 50.f, GetColor(r, g, b));
  randomRect->AddComponent<AutoDestroyComponent>(10.f);
  auto randomRectDragComp = randomRect->AddComponent<DragComponent>();

  randomRectDragComp->cameraSelector = cameraSelector;
  this->AddObject(randomRect);

  GameObjectPtr randomRectChild = std::make_shared<GameObject>("randomRectChild");
  randomRectChild->SetLayer(l);
  randomRectChild->SetOrderInLayer(oIL + 1);
  auto randomRectChildTransComp =
      randomRectChild->AddComponent<TransformComponent>(45.f, 45.f);
  randomRectChild->AddComponent<Rect2DComponent>(10.f, 10.f,
                                                 GetColor(236, 154, 41));

  randomRectChildTransComp->SetParent(randomRect);
  this->AddObject(randomRectChild);
}
