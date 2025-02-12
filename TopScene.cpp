#include "TopScene.h"
#include <memory>
#include "TransformComponent.h"
#include "PointUIComponent.h"
#include "DxLib.h"

void TopScene::Start()
{
	auto point2d = std::make_shared<GameObject>("point2d");
	point2d->AddComponent<TransformComponent>(320, 240);
	point2d->AddComponent<PointUIComponent>(GetColor(255, 0, 0));

	AddObject(point2d);
}
