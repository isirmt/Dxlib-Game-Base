#include "Rect2DComponent.h"
#include "Dxlib.h"
#include "GameObject.h"
#include "TransformComponent.h"

void Rect2DComponent::Render()
{
	auto transform = GetGameObject()->GetComponent<TransformComponent>();
	if (!transform) return;

	float x = transform->worldX;
	float y = transform->worldY;

	float width = sx * transform->worldScaleX;
	float height = sy * transform->worldScaleY;

	DrawBoxAA(x, y, x + width, y + height, color, true);
}
