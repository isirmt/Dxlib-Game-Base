#include "TopScene.h"
#include <memory>
#include "TransformComponent.h"
#include "Point2DComponent.h"
#include "Rect2DComponent.h"
#include "Camera2DComponent.h"
#include "DxLib.h"

void TopScene::Start()
{
	offscreenHandle = MakeScreen(1920, 1080, true);

	AddObject(std::make_shared<GameObject>("point2d")->
		AddComponent<TransformComponent>(320.f, 240.f)->
		AddComponent<Point2DComponent>(GetColor(255, 0, 0))
	);
	AddObject(std::make_shared<GameObject>("rect2d")->
		AddComponent<TransformComponent>(500.f, 300.f)->
		AddComponent<Rect2DComponent>(200.f, 50.f, GetColor(255, 255, 0))
	);

	AddCamera(std::make_shared<GameObject>("camera1")->
		AddComponent<Camera2DComponent>(0, 0, 1920 / 2, 1080 / 2, 0, 0, 1920 / 2, 1080 / 2)
	);
	AddCamera(std::make_shared<GameObject>("camera2")->
		AddComponent<Camera2DComponent>(1920 / 2 + 1, 1080 / 2 + 1, 1920 / 2, 1080 / 2, 1920 / 2 + 1, 1080 / 2 + 1, 1920 / 2, 1080 / 2)
	);

	auto canvas = std::make_shared<GameObject>("Canvas")->
		AddComponent<TransformComponent>(0.f, 0.f);
	// キャンバスの子にオブジェクトを追加
	auto button = std::make_shared<GameObject>("Button")->
		AddComponent<TransformComponent>(100.f, 100.f)-> /* ローカル座標 */
		AddComponent<Rect2DComponent>(150.f, 50.f, GetColor(0, 255, 0));
	
	canvas->AddChild(button);
	AddUIObject(canvas);
}
