#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <string>
#include "Component.h"
//#include "TransformComponent.h"

using GameObjectPtr = std::shared_ptr<GameObject>;
using ComponentPtr = std::shared_ptr<Component>;

class GameObject : public std::enable_shared_from_this<GameObject>
{
	std::unordered_map<std::type_index, ComponentPtr> components_;
	std::vector<std::string> tags;
	bool shouldDestroy;

public:
	std::string name;

	GameObject(std::string _name);

	template <typename T, typename... Args>
		requires std::is_constructible_v<T, Args...>
	std::shared_ptr<T> AddComponent(Args&&... args)
	{
		auto comp = std::make_shared<T>(std::forward<Args>(args)...);
		comp->SetGameObject(shared_from_this());
		components_[typeid(T)] = comp;
		return comp;
	}

	template <typename T>
	std::shared_ptr<T> GetComponent()
	{
		auto it = components_.find(typeid(T));
		return (it != components_.end())
			? std::dynamic_pointer_cast<T>(it->second)
			: nullptr;
	}

	void AddTag(std::string tag) {
		tags.push_back(tag);
	}

	bool HasTag(std::string tag) {
		return std::find(tags.begin(), tags.end(), tag) != tags.end();
	}

	void Destroy() {
		shouldDestroy = true;
	}

	bool ShouldBeDestroyed() const {
		return shouldDestroy;
	}

	void Update()
	{
		for (auto& [type, component] : components_) {
			component->Update(*this);
		}
	}

	void Render()
	{
		for (auto& [type, component] : components_) {
			component->Render(*this);
		}
	}
};

