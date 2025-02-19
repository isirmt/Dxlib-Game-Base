#include "ColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

bool ColliderComponent::Contains(float x, float y)
{
	auto transform = GetGameObject()->GetComponent<TransformComponent>();
	if (!transform) return false;
	float worldX = transform->worldX;
	float worldY = transform->worldY;
	return (x >= worldX && x <= worldX + width &&
		y >= worldY && y <= worldY + height);
}
