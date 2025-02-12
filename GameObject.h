#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <string>
#include "Component.h"

class GameObject
{
	std::unordered_map<std::type_index, std::shared_ptr<Component>> components_;

public:
	std::string name;

	GameObject(std::string _name) : name(_name) {}

	template <typename T, typename... Args>
	void AddComponent(Args&&... args)
	{
		components_[typeid(T)] = std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	std::shared_ptr<T> GetComponent()
	{
		auto it = components_.find(typeid(T));
		return (it != components_.end())
			? std::dynamic_pointer_cast<T>(it->second)
			: nullptr;
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

