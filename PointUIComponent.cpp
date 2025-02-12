#include "PointUIComponent.h"
#include "TransformComponent.h"
#include "DxLib.h"
#include "GameObject.h"

void PointUIComponent::Render(GameObject& obj)
{
	auto transform = obj.GetComponent<TransformComponent>();
	// カメラコンポーネント追加時に変更
	DrawPixel(transform->x, transform->y, color);
}
