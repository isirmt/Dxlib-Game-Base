#include "TopScene.h"
#include <memory>
#include "TransformComponent.h"
#include "Point2DComponent.h"
#include "Rect2DComponent.h"
#include "Camera2DComponent.h"
#include "ButtonComponent.h"
#include "DragComponent.h"
#include "DxLib.h"
#include "CameraMouseCoordinateConverter.h"
#include "AutoDestroyComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"

void TopScene::Start()
{
	ResourceManager::GetInstance().LoadFont("Meiryo", 20, -1);

	RegisterRenderTarget(0, 1280, 720);
	RegisterRenderTarget(1, 1500, 500);
	RegisterRenderTarget(2, 500, 500);

	// カメラ

	GameObjectPtr camera1 = std::make_shared<GameObject>("camera1");
	camera1->SetLayer(0);
	camera1->AddComponent<TransformComponent>(0.f, 0.f);
	camera1->AddComponent<Camera2DComponent>(
		0, 0, 1280 / 2, 720,
		1280 / 2 / 2, 720 / 2,
		camera1->GetLayer()
	);
	camera1->AddTag("Camera");
	cameraSelector->cameras.push_back(camera1);
	AddObject(camera1);

	GameObjectPtr camera2 = std::make_shared<GameObject>("camera2");
	camera2->SetLayer(0);
	camera2->AddComponent<TransformComponent>(1280.f / 2 + 50.f, 0.f);
	camera2->AddComponent<Camera2DComponent>(
		1280 / 2, 0, 1280 / 2, 720,
		1280 / 2, 720,
		camera2->GetLayer()
	);
	camera2->AddTag("Camera");
	cameraSelector->cameras.push_back(camera2);
	AddObject(camera2);

	GameObjectPtr camera3 = std::make_shared<GameObject>("camera3");
	camera3->SetLayer(1);
	auto camera3TComp = camera3->AddComponent<TransformComponent>(0.f, 40.f);
	camera3->AddComponent<Camera2DComponent>(
		0, 0, 1500, 500,
		750, 250,
		camera3->GetLayer()
	);
	camera3->AddTag("Camera");
	camera3->SetOrderInLayer(15);
	cameraSelector->cameras.push_back(camera3);
	AddObject(camera3);

	GameObjectPtr camera4 = std::make_shared<GameObject>("camera4");
	camera4->SetLayer(2);
	auto camera4TComp = camera4->AddComponent<TransformComponent>(0.f, 40.f);
	camera4->AddComponent<Camera2DComponent>(
		0, 0, 500, 500,
		500, 500,
		camera4->GetLayer()
	);
	camera4->AddTag("Camera");
	camera4->SetOrderInLayer(20);
	cameraSelector->cameras.push_back(camera4);
	AddObject(camera4);

	// 背景設定
	GameObjectPtr backRectLeft = std::make_shared<GameObject>("backRectLeft");
	backRectLeft->SetLayer(0);
	backRectLeft->AddComponent<TransformComponent>(0.f, 0.f);
	backRectLeft->AddComponent<Rect2DComponent>(1280.f / 2, 720.f, GetColor(20, 0, 0));
	backRectLeft->AddTag("Object");
	AddObject(backRectLeft);

	GameObjectPtr backRectRight = std::make_shared<GameObject>("backRectRight");
	backRectRight->SetLayer(0);
	backRectRight->AddComponent<TransformComponent>(1280.f / 2.f, 0.f);
	backRectRight->AddComponent<Rect2DComponent>(1280.f / 2, 720.f, GetColor(0, 20, 0));
	backRectRight->AddTag("Object");
	AddObject(backRectRight);

	GameObjectPtr back2RectRight = std::make_shared<GameObject>("back2RectRight");
	back2RectRight->SetLayer(1);
	back2RectRight->AddComponent<TransformComponent>(0.f, 0.f);
	back2RectRight->AddComponent<Rect2DComponent>(1500.f, 500.f, GetColor(0, 0, 20));
	back2RectRight->AddTag("Object");
	AddObject(back2RectRight);

	GameObjectPtr back3RectRight = std::make_shared<GameObject>("back2RectRight");
	back3RectRight->SetLayer(2);
	back3RectRight->AddComponent<TransformComponent>(0.f, 0.f);
	back3RectRight->AddComponent<Rect2DComponent>(500.f, 500.f, GetColor(20, 20, 20));
	back3RectRight->AddTag("Object");
	AddObject(back3RectRight);

	GameObjectPtr text1 = std::make_shared<GameObject>("text1");
	text1->SetLayer(0);
	text1->AddComponent<TransformComponent>(1280.f / 2, 30.f);
	text1->AddComponent<Rect2DComponent>(200.f, 150.f, GetColor(20, 20, 20));
	text1->AddComponent<TextComponent>(
		"Hello World! ハローワールド！ おはよう！",
		ResourceManager::GetInstance().LoadFont("Meiryo", 20, -1),
		GetColor(255, 255, 255),
		80,
		30
	);
	auto text1DComp = text1->AddComponent<DragComponent>();
	text1DComp->cameraSelector = cameraSelector;
	text1DComp->mouseProvider = mouseProvider;
	text1->AddTag("Object");

	AddObject(text1);

	GameObjectPtr point2d = std::make_shared<GameObject>("point2d");
	point2d->SetLayer(0);
	point2d->AddComponent<TransformComponent>(320.f, 240.f);
	point2d->AddComponent<Point2DComponent>(GetColor(255, 0, 0));
	point2d->AddTag("Object");
	AddObject(point2d);

	GameObjectPtr rect2d = std::make_shared<GameObject>("rect2d");
	rect2d->SetLayer(1);
	rect2d->AddComponent<TransformComponent>(500.f, 300.f);
	rect2d->AddComponent<Rect2DComponent>(400.f, 100.f, GetColor(255, 0, 0));
	rect2d->AddTag("Object");
	AddObject(rect2d);

	// ボタン
	GameObjectPtr wButton1 = std::make_shared<GameObject>("wButton1");
	wButton1->SetLayer(0);
	wButton1->AddComponent<TransformComponent>(800.f, 600.f);
	wButton1->AddComponent<Rect2DComponent>(200.f, 40.f, GetColor(0, 0, 255));
	wButton1->AddComponent<TextComponent>(
		"ボタン1",
		ResourceManager::GetInstance().LoadFont("Meiryo", 20, -1),
		GetColor(255, 255, 255),
		0
	);
	auto wButton1BComp = wButton1->AddComponent<ButtonComponent>();
	wButton1BComp->mouseProvider = mouseProvider;
	wButton1BComp->cameraSelector = cameraSelector;
	wButton1BComp->AddOnClickListener(std::bind(&TopScene::OnButtonClickedMember, this));
	auto wButton1DComp = wButton1->AddComponent<DragComponent>();
	wButton1DComp->cameraSelector = cameraSelector;
	wButton1DComp->mouseProvider = mouseProvider;
	wButton1->AddTag("Object");
	AddObject(wButton1);

	GameObjectPtr camera3Frame = std::make_shared<GameObject>("camera3Frame");
	camera3Frame->AddComponent<TransformComponent>(50.f, 400.f);
	camera3Frame->AddComponent<Rect2DComponent>(750.f, 40.f, GetColor(0, 255, 255));
	camera3Frame->AddComponent<TextComponent>(
		"レイヤー1のカメラ(ドラッグ可)",
		ResourceManager::GetInstance().LoadFont("Meiryo", 20, -1),
		GetColor(50, 50, 200),
		0
	);
	auto camera3FrameDComp = camera3Frame->AddComponent<DragComponent>();
	camera3FrameDComp->mouseProvider = mouseProvider;
	camera3Frame->AddTag("UI");
	camera3Frame->SetOrderInLayer(10); // UI扱いにするが，他UIより下にする
	AddObject(camera3Frame);

	camera3TComp->SetParent(camera3Frame);

	GameObjectPtr camera4Frame = std::make_shared<GameObject>("camera4Frame");
	camera4Frame->AddComponent<TransformComponent>(400.f, 200.f);
	camera4Frame->AddComponent<Rect2DComponent>(500.f, 40.f, GetColor(255, 255, 255));
	camera4Frame->AddComponent<TextComponent>(
		"レイヤー2のカメラ(ドラッグ可)",
		ResourceManager::GetInstance().LoadFont("Meiryo", 20, -1),
		GetColor(50, 50, 200),
		0
	);
	auto camera4FrameDComp = camera4Frame->AddComponent<DragComponent>();
	camera4FrameDComp->mouseProvider = mouseProvider;
	camera4Frame->AddTag("UI");
	camera4Frame->SetOrderInLayer(15); // UI扱いにするが，他UIより下にする
	AddObject(camera4Frame);

	camera4TComp->SetParent(camera4Frame);

	// タグ「UI」を指定
	GameObjectPtr canvas = std::make_shared<GameObject>("canvas");
	canvas->AddComponent<TransformComponent>(0.f, 0.f);
	canvas->AddTag("UI");
	AddObject(canvas);

	GameObjectPtr canvasButton = std::make_shared<GameObject>("canvasButton");
	auto canvasButtonTComp = canvasButton->AddComponent<TransformComponent>(100.f, 100.f); // ローカル座標
	canvasButton->AddComponent<Rect2DComponent>(150.f, 50.f, GetColor(0, 255, 0));
	canvasButtonTComp->SetParent(canvas);
	auto canvasButtonBComp = canvasButton->AddComponent<ButtonComponent>();
	canvasButtonBComp->mouseProvider = mouseProvider;
	canvasButton->AddTag("UI");
	AddObject(canvasButton);
}

void TopScene::OnButtonClickedMember()
{
	int randX = GetRand(1280);
	int randY = GetRand(720);
	int r = GetRand(256);
	int g = GetRand(256);
	int b = GetRand(256);
	int l = GetRand(2);

	// ドラッグ操作可能
	GameObjectPtr randomRectObj = std::make_shared<GameObject>("randomRect");
	randomRectObj->SetLayer(l);
	randomRectObj->AddComponent<TransformComponent>(static_cast<float>(randX), static_cast<float>(randY));
	randomRectObj->AddComponent<Rect2DComponent>(50.f, 50.f, GetColor(r, g, b));
	randomRectObj->AddComponent<AutoDestroyComponent>(3.f);
	randomRectObj->AddTag("Object");
	auto dragComp = randomRectObj->AddComponent<DragComponent>();
	dragComp->cameraSelector = cameraSelector;
	this->AddObject(randomRectObj);

	GameObjectPtr attachedRectObj = std::make_shared<GameObject>("attachedRectObj");
	attachedRectObj->SetLayer(randomRectObj->GetLayer());
	attachedRectObj->AddComponent<TransformComponent>(45.f, 45.f)->SetParent(randomRectObj);
	attachedRectObj->AddComponent<Rect2DComponent>(7.f, 7.f, GetColor(200, 200, 40));
	attachedRectObj->AddTag("Object");
	this->AddObject(attachedRectObj);

}
