#include "TopScene.h"
#include <memory>
#include "TransformComponent.h"
#include "Point2DComponent.h"
#include "Rect2DComponent.h"
#include "Camera2DComponent.h"
#include "ButtonComponent.h"
#include "DxLib.h"
#include "CameraMouseCoordinateConverter.h"
#include "AutoDestroyComponent.h"

void TopScene::Start()
{
	offscreenHandle = MakeScreen(1280, 720, true);

	//GameObjectPtr camera1 = std::make_shared<GameObject>("camera1");
	//camera1->AddComponent<Camera2DComponent>(
	//	0, 0, 1280, 720,
	//	0, 0, 1280, 720
	//);
	//AddCamera(camera1);

	GameObjectPtr camera1 = std::make_shared<GameObject>("camera1");
	camera1->AddComponent<Camera2DComponent>(
		0, 0, 1280 / 2, 720,
		0, 0, 1280 / 2, 720
	);
	camera1->AddTag("Camera");
	AddObject(camera1);

	GameObjectPtr camera2 = std::make_shared<GameObject>("camera2");
	camera2->AddComponent<Camera2DComponent>(
		1280 / 2, 0, 1280 / 2, 720,
		1280 / 2 + 0 /* Test */, 0, 1280 / 2, 720
	);
	camera2->AddTag("Camera");
	AddObject(camera2);


	GameObjectPtr point2d = std::make_shared<GameObject>("point2d");
	point2d->AddComponent<TransformComponent>(320.f, 240.f);
	point2d->AddComponent<Point2DComponent>(GetColor(255, 0, 0));
	point2d->AddTag("Object");
	AddObject(point2d);

	GameObjectPtr rect2d = std::make_shared<GameObject>("rect2d");
	rect2d->AddComponent<TransformComponent>(500.f, 300.f);
	rect2d->AddComponent<Rect2DComponent>(400.f, 100.f, GetColor(255, 255, 0));
	rect2d->AddTag("Object");
	AddObject(rect2d);

	GameObjectPtr wButton1 = std::make_shared<GameObject>("wButton1");
	wButton1->AddComponent<TransformComponent>(800.f, 600.f);
	wButton1->AddComponent<Rect2DComponent>(200.f, 40.f, GetColor(0, 0, 255));
	auto wButton1BComp = wButton1->AddComponent<ButtonComponent>();
	wButton1BComp->cameraSelector = cameraSelector;
	wButton1BComp->AddOnClickListener(std::bind(&TopScene::OnButtonClickedMember, this));
	wButton1->AddTag("Object");
	AddObject(wButton1);


	GameObjectPtr canvas = std::make_shared<GameObject>("canvas");
	canvas->AddComponent<TransformComponent>(0.f, 0.f);
	// キャンバスの子にオブジェクトを追加
	GameObjectPtr canvasButton = std::make_shared<GameObject>("button");
	auto canvasButtonTComp = canvasButton->AddComponent<TransformComponent>(100.f, 100.f); /* ローカル座標 */
	canvasButton->AddComponent<Rect2DComponent>(150.f, 50.f, GetColor(0, 255, 0));
	canvasButtonTComp->SetParent(canvas);

	canvas->AddTag("UI");
	canvasButton->AddTag("UI");
	AddObject(canvas);
	AddObject(canvasButton);
}

void TopScene::OnButtonClickedMember()
{
	int randX = GetRand(1280);
	int randY = GetRand(720);
	int r = GetRand(256);
	int g = GetRand(256);
	int b = GetRand(256);

	GameObjectPtr randomRectObj = std::make_shared<GameObject>("randomRect");
	randomRectObj->AddComponent<TransformComponent>(static_cast<float>(randX), static_cast<float>(randY));
	randomRectObj->AddComponent<Rect2DComponent>(50.f, 50.f, GetColor(r, g, b));
	randomRectObj->AddComponent<AutoDestroyComponent>(60 * 3);
	randomRectObj->AddTag("Object");
	this->AddObject(randomRectObj);
}
