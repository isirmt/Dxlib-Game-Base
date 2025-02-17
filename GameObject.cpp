#include "GameObject.h"
#include "TransformComponent.h"

void GameObject::Destroy()
{
    shouldDestroy = true;

    auto transform = GetComponent<TransformComponent>();
    if (transform) {
        for (auto& childObj : transform->children) {
            if (childObj) {
                childObj->Destroy();
            }
        }
    }
}

void GameObject::SetActive(bool flag)
{
	active = flag;

	auto transform = GetComponent<TransformComponent>();
	if (transform) {
		for (auto& childObj : transform->children) {
			if (childObj) {
				childObj->SetActive(flag);
			}
		}
	}
}

void GameObject::SetVisible(bool flag)
{
	visible = flag;

	auto transform = GetComponent<TransformComponent>();
	if (transform) {
		for (auto& childObj : transform->children) {
			if (childObj) {
				childObj->SetVisible(flag);
			}
		}
	}
}
