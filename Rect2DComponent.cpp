#include "Rect2DComponent.h"
#include "Dxlib.h"
#include "GameObject.h"
#include "TransformComponent.h"

void Rect2DComponent::Render(GameObject& obj)
{
	auto transform = obj.GetComponent<TransformComponent>();
	// カメラコンポーネント追加時に変更
	DrawBox(transform->x, transform->y, sx + transform->x, sy + transform->y, color, true);
}
