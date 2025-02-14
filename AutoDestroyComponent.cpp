#include "AutoDestroyComponent.h"
#include "GameObject.h"

void AutoDestroyComponent::Update(GameObject& obj)
{
	remain--;

	if (remain <= 0) {
		obj.Destroy();
	}
}
