#include "AutoDestroyComponent.h"
#include "GameObject.h"
#include "Time.h"

void AutoDestroyComponent::Update()
{
	Time& time = Time::GetInstance();
	remain -= time.GetDeltaTime();

	if (remain <= 0.f) {
		GetGameObject()->Destroy();
	}
}
