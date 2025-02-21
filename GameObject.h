#pragma once
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>

#include "Component.h"

using GameObjectPtr = std::shared_ptr<GameObject>;
using ComponentPtr = std::shared_ptr<Component>;

/**
 * @brief シーンに配置されるオブジェクト．コンポーネント形式で動作する
 */
class GameObject : public std::enable_shared_from_this<GameObject> {
  std::unordered_map<std::type_index, ComponentPtr> components_;
  bool shouldDestroy = false;
  int layer = 0;
  int orderInLayer = 0;
  bool active = true;
  bool visible = true;

 public:
  /**
   * @brief オブジェクト名
   */
  std::string name;

  /**
   * @brief オブジェクトの初期化
   * @param _name オブジェクト名(デバッグで有効的)
   */
  GameObject(std::string _name = "GameObject") : name(_name) {}

  /**
   * @brief コンポーネントの追加
   * @tparam T コンポーネント派生の型
   * @tparam ...Args コンポーネントの引数型
   * @param ...args コンポーネントの引数
   * @return コンポーネントのポインタ
   */
  template <typename T, typename... Args>
    requires std::is_constructible_v<T, Args...>
  std::shared_ptr<T> AddComponent(Args&&... args) {
    auto comp = std::make_shared<T>(std::forward<Args>(args)...);
    comp->SetGameObject(shared_from_this());
    components_[typeid(T)] = comp;
    return comp;
  }

  /**
   * @brief コンポーネントの取得
   * @tparam T 派生コンポーネントの型
   * @return コンポーネントのポインタ(nullptrは登録されていないを表す)
   */
  template <typename T>
  std::shared_ptr<T> GetComponent() {
    auto it = components_.find(typeid(T));
    return (it != components_.end()) ? std::dynamic_pointer_cast<T>(it->second)
                                     : nullptr;
  }

  /**
   * @brief レイヤー内の表示順序を設定する
   * @param order 表示順序
   */
  void SetOrderInLayer(int order) { orderInLayer = order; }
  /**
   * @brief レイヤー内の表示順序を取得する
   * @return 表示順序
   */
  int GetOrderInLayer() const { return orderInLayer; }

  /**
   * @brief レイヤー(描画先のキャンバス)を指定する
   * @param _layer 対象のキャンバス
   */
  void SetLayer(int _layer) { layer = _layer; }
  /**
   * @brief レイヤーを取得する
   * @return レイヤー
   */
  int GetLayer() const { return layer; }

  /**
   * @brief オブジェクト(とその子オブジェクト)を破棄する
   */
  void Destroy();

  /**
   * @brief 破棄される予定か
   * @return TRUE: 破棄される予定
   */
  bool ShouldBeDestroyed() const { return shouldDestroy; }

  /**
   * @brief オブジェクトの有効性を設定する
   * @param flag
   */
  void SetActive(bool flag);
  /**
   * @brief オブジェクトが有効か
   * @return TRUE: 有効
   */
  bool IsActive() const { return active; }

  /**
   * @brief オブジェクトが見えるかどうか設定する
   * @param flag
   */
  void SetVisible(bool flag);
  /**
   * @brief オブジェクトが見えるか
   * @return TRUE: 見える
   */
  bool IsVisible() const { return visible; }

  /**
   * @brief オブジェクトのコンポーネントを更新する
   */
  void Update() {
    if (!active) return;
    for (auto& [type, component] : components_) {
      component->Update();
    }
  }

  /**
   * @brief オブジェクトのコンポーネントで描画する
   */
  void Render() {
    if (!active || !visible) return;
    for (auto& [type, component] : components_) {
      component->Render();
    }
  }
};
