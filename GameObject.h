#pragma once
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>

#include "Component.h"

using GameObjectPtr = std::shared_ptr<GameObject>;
using ComponentPtr = std::shared_ptr<Component>;

class GameObject : public std::enable_shared_from_this<GameObject> {
  std::unordered_map<std::type_index, ComponentPtr> components_;
  bool shouldDestroy = false;
  int layer = 0;
  int orderInLayer = 0;
  bool active = true;
  bool visible = true;

 public:
  std::string name;

  GameObject(std::string _name = "GameObject") : name(_name) {}

  template <typename T, typename... Args>
    requires std::is_constructible_v<T, Args...>
  std::shared_ptr<T> AddComponent(Args&&... args) {
    auto comp = std::make_shared<T>(std::forward<Args>(args)...);
    comp->SetGameObject(shared_from_this());
    components_[typeid(T)] = comp;
    return comp;
  }

  template <typename T>
  std::shared_ptr<T> GetComponent() {
    auto it = components_.find(typeid(T));
    return (it != components_.end()) ? std::dynamic_pointer_cast<T>(it->second)
                                     : nullptr;
  }

  void SetOrderInLayer(int order) { orderInLayer = order; }
  int GetOrderInLayer() const { return orderInLayer; }

  void SetLayer(int _layer) { layer = _layer; }
  int GetLayer() const { return layer; }

  void Destroy();

  bool ShouldBeDestroyed() const { return shouldDestroy; }

  void SetActive(bool flag);

  bool IsActive() const { return active; }

  void SetVisible(bool flag);

  bool IsVisible() const { return visible; }

  void Update() {
    if (!active) return;
    for (auto& [type, component] : components_) {
      component->Update();
    }
  }

  void Render() {
    if (!active || !visible) return;
    for (auto& [type, component] : components_) {
      component->Render();
    }
  }
};
