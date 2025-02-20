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
  RegisterRenderTarget(1, 1000, 1000);
  RegisterRenderTarget(2, 1280, 720);

  RegisterRenderTarget(3, 500, 500);
  RegisterRenderTarget(4, 1280, 720);

  {
    // カメラ: 背景描画用
    GameObjectPtr camera0 = CreateObject("camera0");
    camera0->SetLayer(0);
    camera0->AddComponent<TransformComponent>(0.f, 0.f);
    camera0->AddComponent<Camera2DComponent>(0, 0, 1280, 720, 1280, 720,
                                             camera0->GetLayer());
    AddObject(camera0);
    cameraSelector->cameras.push_back(camera0);

    // 背景: カメラ0
    GameObjectPtr camera0BackRect = CreateObject("camera0BackRect");
    camera0BackRect->SetLayer(camera0->GetLayer());
    camera0BackRect->SetOrderInLayer(-100);
    camera0BackRect->AddComponent<TransformComponent>();
    camera0BackRect->AddComponent<Rect2DComponent>(1280.f, 720.f,
                                                   GetColor(239, 241, 243));
    camera0BackRect->AddComponent<TextComponent>(
        "カメラ0描画部分", meiryo30, GetColor(100, 100, 100));

    AddObject(camera0BackRect);

    GameObjectPtr rectSpawningButton0 = CreateObject("rectSpawningButton0");
    rectSpawningButton0->SetLayer(camera0->GetLayer());
    rectSpawningButton0->SetOrderInLayer(5);
    rectSpawningButton0->AddComponent<TransformComponent>(100.f, 400.f);
    auto rectSpawningButton0DragComp =
        rectSpawningButton0->AddComponent<DragComponent>();
    rectSpawningButton0->AddComponent<ColliderComponent>(250.f, 150.f);
    rectSpawningButton0->AddComponent<Rect2DComponent>(250.f, 150.f,
                                                       GetColor(118, 137, 72));
    rectSpawningButton0->AddComponent<TextComponent>(
        "[ドラッグ可能]\nレイヤー０オブジェクト", meiryo20,
        GetColor(10, 10, 10), 250, 45);

    rectSpawningButton0DragComp->cameraSelector = cameraSelector;
    rectSpawningButton0DragComp->cancelDraggingOnConverterNull = true;
    AddObject(rectSpawningButton0);
  }

  {
    // カメラ1: 浮遊ウインドウのメイン部分
    GameObjectPtr camera1 = CreateObject("camera1");
    camera1->SetLayer(1);
    auto camera1TransComp =
        camera1->AddComponent<TransformComponent>(0.f, 40.f);
    camera1->AddComponent<Camera2DComponent>(0, 0, 1000, 1000, 500, 500,
                                             camera1->GetLayer());
    AddObject(camera1);
    cameraSelector->cameras.push_back(camera1);

    // 背景: カメラ1
    GameObjectPtr camera1BackRect = CreateObject("camera1BackRect");
    camera1BackRect->SetLayer(camera1->GetLayer());
    camera1BackRect->SetOrderInLayer(-100);
    camera1BackRect->AddComponent<TransformComponent>();
    camera1BackRect->AddComponent<ColliderComponent>(1000.f, 1000.f);
    camera1BackRect->AddComponent<Rect2DComponent>(1000.f, 1000.f,
                                                   GetColor(219, 211, 216));
    camera1BackRect->AddComponent<TextComponent>("カメラ1描画部分", meiryo30,
                                                 GetColor(40, 40, 40));
    AddObject(camera1BackRect);

    GameObjectPtr rectSpawningButton1 = CreateObject("rectSpawningButton1");
    rectSpawningButton1->SetLayer(camera1->GetLayer());
    rectSpawningButton1->SetOrderInLayer(5);
    rectSpawningButton1->AddComponent<TransformComponent>(100.f, 100.f);
    auto rectSpawningButton1DragComp =
        rectSpawningButton1->AddComponent<DragComponent>();
    rectSpawningButton1->AddComponent<ColliderComponent>(250.f, 150.f);
    rectSpawningButton1->AddComponent<Rect2DComponent>(250.f, 150.f,
                                                       GetColor(75, 136, 162));
    rectSpawningButton1->AddComponent<TextComponent>(
        "[ドラッグ可能]\nレイヤー１オブジェクト", meiryo30,
        GetColor(10, 10, 10), 250, 45);

    rectSpawningButton1DragComp->cameraSelector = cameraSelector;
    rectSpawningButton1DragComp->cancelDraggingOnConverterNull = true;
    AddObject(rectSpawningButton1);

    // カメラ2: バナー部分
    GameObjectPtr camera2 = CreateObject("camera2");
    camera2->SetLayer(2);
    camera2->AddComponent<TransformComponent>();
    camera2->AddComponent<Camera2DComponent>(0, 0, 1280, 720, 1280, 720,
                                             camera2->GetLayer());
    AddObject(camera2);
    cameraSelector->cameras.push_back(camera2);

    // 背景: カメラ2
    GameObjectPtr camera2BackRect = CreateObject("camera2BackRect");
    camera2BackRect->SetLayer(camera2->GetLayer());
    camera2BackRect->SetOrderInLayer(-100);
    camera2BackRect->AddComponent<TransformComponent>(500.f, 60.f);
    camera2BackRect->AddComponent<ColliderComponent>(500.f, 40.f);
    auto camera2BackRectDragComp =
        camera2BackRect->AddComponent<DragComponent>();
    camera2BackRect->AddComponent<Rect2DComponent>(500.f, 40.f,
                                                   GetColor(34, 56, 67));
    camera2BackRect->AddComponent<TextComponent>(
        "[ドラッグ可能] カメラ2", meiryo30, GetColor(200, 200, 200));

    camera2BackRectDragComp->cameraSelector = cameraSelector;
    AddObject(camera2BackRect);

    { camera1TransComp->SetParent(camera2BackRect); }
  }

  {
    // カメラ3: 浮遊ウインドウのメイン部分
    GameObjectPtr camera3 = CreateObject("camera3");
    camera3->SetLayer(3);
    auto camera3TransComp =
        camera3->AddComponent<TransformComponent>(0.f, 40.f);
    camera3->AddComponent<Camera2DComponent>(0, 0, 500, 500, 500, 500,
                                             camera3->GetLayer());
    AddObject(camera3);
    cameraSelector->cameras.push_back(camera3);

    // 背景: カメラ3
    GameObjectPtr camera3BackRect = CreateObject("camera3BackRect");
    camera3BackRect->SetLayer(camera3->GetLayer());
    camera3BackRect->SetOrderInLayer(-100);
    camera3BackRect->AddComponent<TransformComponent>();
    camera3BackRect->AddComponent<ColliderComponent>(500.f, 500.f);
    camera3BackRect->AddComponent<Rect2DComponent>(500.f, 500.f,
                                                   GetColor(216, 203, 199));
    camera3BackRect->AddComponent<TextComponent>(
        "カメラ3描画部分", meiryo30, GetColor(40, 40, 40));

    AddObject(camera3BackRect);

    GameObjectPtr rectSpawningButton3 = CreateObject("rectSpawningButton3");
    rectSpawningButton3->SetLayer(camera3->GetLayer());
    rectSpawningButton3->SetOrderInLayer(5);
    rectSpawningButton3->AddComponent<TransformComponent>(100.f, 100.f);
    auto rectSpawningButton3DragComp =
        rectSpawningButton3->AddComponent<DragComponent>();
    rectSpawningButton3->AddComponent<ColliderComponent>(250.f, 200.f);
    rectSpawningButton3->AddComponent<Rect2DComponent>(250.f, 200.f,
                                                       GetColor(187, 10, 33));
    rectSpawningButton3->AddComponent<TextComponent>(
        "[ドラッグ可能]\n[離トリガー]\nレイヤー３オブジェクト", meiryo30,
        GetColor(10, 10, 10), 250, 45);
    auto rectSpawningButton3ButtonComp =
        rectSpawningButton3->AddComponent<ButtonComponent>();

    rectSpawningButton3DragComp->cameraSelector = cameraSelector;
    rectSpawningButton3ButtonComp->cameraSelector = cameraSelector;
    rectSpawningButton3ButtonComp->AddOnClickListener(
        std::bind(&TopScene::OnButtonClickedMember, this));
    AddObject(rectSpawningButton3);

    // カメラ4: バナー部分
    GameObjectPtr camera4 = CreateObject("camera4");
    camera4->SetLayer(4);
    camera4->AddComponent<TransformComponent>();
    camera4->AddComponent<Camera2DComponent>(0, 0, 1280, 720, 1280, 720,
                                             camera4->GetLayer());
    AddObject(camera4);
    cameraSelector->cameras.push_back(camera4);

    // 背景: カメラ4
    GameObjectPtr camera4BackRect = CreateObject("camera4BackRect");
    camera4BackRect->SetLayer(camera4->GetLayer());
    camera4BackRect->SetOrderInLayer(-100);
    camera4BackRect->AddComponent<TransformComponent>(700.f, 150.f);
    camera4BackRect->AddComponent<ColliderComponent>(500.f, 40.f);
    auto camera4BackRectDragComp =
        camera4BackRect->AddComponent<DragComponent>();
    camera4BackRect->AddComponent<Rect2DComponent>(500.f, 40.f,
                                                   GetColor(46, 53, 50));
    camera4BackRect->AddComponent<TextComponent>(
        "[ドラッグ可能] カメラ4", meiryo30, GetColor(200, 200, 200));

    camera4BackRectDragComp->cameraSelector = cameraSelector;
    AddObject(camera4BackRect);

    { camera3TransComp->SetParent(camera4BackRect); }
  }

  {
    // 定点カメラ5
    GameObjectPtr camera5 = CreateObject("camera5");
    camera5->SetLayer(3);
    camera5->AddComponent<TransformComponent>(20.f, 500.f);
    camera5->AddComponent<Camera2DComponent>(0, 0, 500, 500, 200, 200,
                                             3);
    AddObject(camera5);
    // 判定に入れない場合，cameraSelectorへは登録しない
    //cameraSelector->cameras.push_back(camera5);

    GameObjectPtr caption = CreateObject("caption");
    caption->SetLayer(0);
    caption->SetOrderInLayer(1000);
    caption->AddComponent<TransformComponent>(230.f, 680.f);
    caption->AddComponent<TextComponent>("← レイヤー3 ミニマップ", meiryo20, GetColor(30, 30, 30));
    AddObject(caption);
  }
}

void TopScene::OnButtonClickedMember() {
  int randX = GetRand(500);
  int randY = GetRand(500);
  int r = GetRand(256);
  int g = GetRand(256);
  int b = GetRand(256);
  int l = GetRand(5);  // == 5のみ表示されない
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

  GameObjectPtr randomRectChild =
      std::make_shared<GameObject>("randomRectChild");
  randomRectChild->SetLayer(l);
  randomRectChild->SetOrderInLayer(oIL + 1);
  auto randomRectChildTransComp =
      randomRectChild->AddComponent<TransformComponent>(45.f, 45.f);
  randomRectChild->AddComponent<Rect2DComponent>(10.f, 10.f,
                                                 GetColor(236, 154, 41));

  randomRectChildTransComp->SetParent(randomRect);
  this->AddObject(randomRectChild);
}
