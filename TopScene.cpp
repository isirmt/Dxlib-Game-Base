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

void TopScene::Start()
{
	RegisterRenderTarget(0, 1280, 720);
	RegisterRenderTarget(1, 1280, 720);

	// カメラ

	GameObjectPtr camera1 = std::make_shared<GameObject>("camera1");
	camera1->SetLayer(0);
	camera1->AddComponent<Camera2DComponent>(
		0, 0, 1280 / 2, 720,
		0, 0, 1280 / 2, 720,
		camera1->GetLayer()
	);
	camera1->AddTag("Camera");
	cameraSelector->cameras.push_back(camera1);
	AddObject(camera1);

	GameObjectPtr camera2 = std::make_shared<GameObject>("camera2");
	camera2->SetLayer(0);
	camera2->AddComponent<Camera2DComponent>(
		1280 / 2, 0, 1280 / 2, 720,
		1280 / 2 + 50, 0, 1280 / 2, 720,
		camera2->GetLayer()
	);
	camera2->AddTag("Camera");
	cameraSelector->cameras.push_back(camera2);
	AddObject(camera2);

	GameObjectPtr camera3 = std::make_shared<GameObject>("camera3");
	camera3->SetLayer(1);
	camera3->AddComponent<Camera2DComponent>(
		0, 0, 1280, 720,
		0, 0, 1280, 720,
		camera3->GetLayer()
	);
	camera3->AddTag("Camera");
	cameraSelector->cameras.push_back(camera3);
	AddObject(camera3);

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
	auto wButton1BComp = wButton1->AddComponent<ButtonComponent>();
	wButton1BComp->cameraSelector = cameraSelector;
	wButton1BComp->AddOnClickListener(std::bind(&TopScene::OnButtonClickedMember, this));
	auto dragComp = wButton1->AddComponent<DragComponent>();
	dragComp->cameraSelector = cameraSelector;
	wButton1->AddTag("Object");
	AddObject(wButton1);

	// タグ「UI」を指定
	GameObjectPtr canvas = std::make_shared<GameObject>("canvas");
	canvas->AddComponent<TransformComponent>(0.f, 0.f);
	canvas->AddTag("UI");
	AddObject(canvas);

	GameObjectPtr canvasButton = std::make_shared<GameObject>("button");
	auto canvasButtonTComp = canvasButton->AddComponent<TransformComponent>(100.f, 100.f); // ローカル座標
	canvasButton->AddComponent<Rect2DComponent>(150.f, 50.f, GetColor(0, 255, 0));
	canvasButtonTComp->SetParent(canvas);
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

	// ドラッグ操作可能
	GameObjectPtr randomRectObj = std::make_shared<GameObject>("randomRect");
	randomRectObj->SetLayer(1);
	randomRectObj->AddComponent<TransformComponent>(static_cast<float>(randX), static_cast<float>(randY));
	randomRectObj->AddComponent<Rect2DComponent>(50.f, 50.f, GetColor(r, g, b));
	randomRectObj->AddComponent<AutoDestroyComponent>(60 * 3);
	randomRectObj->AddTag("Object");
	auto dragComp = randomRectObj->AddComponent<DragComponent>();
	dragComp->cameraSelector = cameraSelector;
	this->AddObject(randomRectObj);

	GameObjectPtr attachedRectObj = std::make_shared<GameObject>("attachedRectObj");
	attachedRectObj->SetLayer(randomRectObj->GetLayer());
	attachedRectObj->AddComponent<TransformComponent>(45.f, 45.f)->SetParent(randomRectObj);
	attachedRectObj->AddComponent<Rect2DComponent>(7.f, 7.f, GetColor(200, 200, 40));
	attachedRectObj->AddComponent<AutoDestroyComponent>(60 * 3);
	attachedRectObj->AddTag("Object");
	this->AddObject(attachedRectObj);

}
