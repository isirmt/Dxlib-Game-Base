#include "AutoDestroyComponent.h"
#include "GameObject.h"

void AutoDestroyComponent::Update()
{
	remain--;

	if (remain <= 0) {
		GetGameObject()->Destroy();
	}
}
