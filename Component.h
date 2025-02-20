#pragma once
#include <memory>

class GameObject;

class Component {
 protected:
  std::weak_ptr<GameObject> gameObject;

 public:
  virtual ~Component() = default;
  virtual void Update() {};
  virtual void Render() {};

  void SetGameObject(std::shared_ptr<GameObject> obj) { gameObject = obj; }
  std::shared_ptr<GameObject> GetGameObject() const {
    return gameObject.lock();
  }
};
