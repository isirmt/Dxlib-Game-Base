#include "TopScene.h"
#include <memory>
#include "TransformComponent.h"
#include "Point2DComponent.h"
#include "Rect2DComponent.h"
#include "DxLib.h"

void TopScene::Start()
{
	AddObject(std::make_shared<GameObject>("point2d")->
		AddComponent<TransformComponent>(320, 240)->
		AddComponent<Point2DComponent>(GetColor(255, 0, 0))
	);
	AddObject(std::make_shared<GameObject>("rect2d")->
		AddComponent<TransformComponent>(500, 300)->
		AddComponent<Rect2DComponent>(200, 50, GetColor(255, 255, 0))
	);
}
