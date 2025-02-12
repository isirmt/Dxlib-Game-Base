#include "PointUIComponent.h"
#include "TransformComponent.h"
#include "DxLib.h"
#include "GameObject.h"

void PointUIComponent::Render(GameObject& obj)
{
	auto transform = obj.GetComponent<TransformComponent>();
	// �J�����R���|�[�l���g�ǉ����ɕύX
	DrawPixel(transform->x, transform->y, color);
}
