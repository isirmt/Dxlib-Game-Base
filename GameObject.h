#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <string>
#include "Component.h"

using GameObjectPtr = std::shared_ptr<GameObject>;
using ComponentPtr = std::shared_ptr<Component>;

class GameObject : public std::enable_shared_from_this<GameObject>
{
	std::unordered_map<std::type_index, ComponentPtr> components_;
	std::vector<GameObjectPtr> children_;

public:
	std::string name;
	std::weak_ptr<GameObject> parent;

	GameObject(std::string _name) : name(_name) {}

	template <typename T, typename... Args>
		requires std::is_constructible_v<T, Args...>
	std::shared_ptr<T> AddComponent(Args&&... args)
	{
		auto comp = std::make_shared<T>(std::forward<Args>(args)...);
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

	GameObjectPtr AddChild(GameObjectPtr child)
	{
		child->parent = shared_from_this();
		children_.push_back(child);
		return shared_from_this();
	}

	void Update()
	{
		for (auto& [type, component] : components_) {
			component->Update(*this);
		}

		for (auto& child : children_) {
			child->Update();
		}
	}

	void Render()
	{
		for (auto& [type, component] : components_) {
			component->Render(*this);
		}

		for (auto& child : children_) {
			child->Render();
		}
	}
};

