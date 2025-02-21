#pragma once
#include <memory>

class GameObject;

/**
 * @brief コンポーネントの抽象クラス
 */
class Component {
 protected:
  /**
   * @brief コンポーネントを保持するゲームオブジェクト
   */
  std::weak_ptr<GameObject> gameObject;

 public:
  virtual ~Component() = default;
  /**
   * @brief 更新関数(デフォルトは何もしない)
   */
  virtual void Update() {};
  /**
   * @brief 描画関数(デフォルトは何もしない)
   */
  virtual void Render() {};

  /**
   * @brief コンポーネントとゲームオブジェクトを紐づける
   * @param obj 紐づけるオブジェクト
   */
  void SetGameObject(std::shared_ptr<GameObject> obj) { gameObject = obj; }
  std::shared_ptr<GameObject> GetGameObject() const {
    return gameObject.lock();
  }
};
