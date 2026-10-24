#pragma once
#include <memory>
#include <vector>

#include "Scene.h"
#include "Singleton.h"

/**
 * @brief シーン管理
 */
class SceneManager : public Singleton<SceneManager> {
  friend class Singleton<SceneManager>;

 private:
  SceneManager() = default;

  std::vector<std::shared_ptr<Scene>> scenes_;
  std::shared_ptr<MouseCameraSelector> cameraSelector;

 public:
  void SetCameraSelector(std::shared_ptr<MouseCameraSelector> _cameraSelector) {
    cameraSelector = _cameraSelector;
  }

  /**
   * @brief シーン変更
   * @tparam T Scene継承の型
   * @tparam ...Args Tのコンストラクタの引数
   * @param ...args
   * @return インスタンス
   */
  template <typename T, typename... Args>
    requires std::is_constructible_v<T, Args...> &&
             std::is_base_of<Scene, T>::value
  std::shared_ptr<T> ChangeScene(Args&&... args) {
    auto newScene = std::make_shared<T>(std::forward<Args>(args)...);
    newScene->SetAdditive(false);
    if (cameraSelector) newScene->SetCameraSelector(cameraSelector);
    scenes_.clear();

    scenes_.push_back(newScene);
    newScene->Start();
    return newScene;
  }

  /**
   * @brief 追加シーンの設定
   * @tparam T Scene継承の型
   * @tparam ...Args Tのコンストラクタの引数
   * @param ...args
   * @return インスタンス
   */
  template <typename T, typename... Args>
    requires std::is_constructible_v<T, Args...> &&
             std::is_base_of<Scene, T>::value
  std::shared_ptr<T> AdditiveScene(Args&&... args) {
    auto additiveScene = std::make_shared<T>(std::forward<Args>(args)...);
    additiveScene->SetAdditive(true);
    if (cameraSelector) additiveScene->SetCameraSelector(cameraSelector);

    scenes_.push_back(additiveScene);
    additiveScene->Start();
    return additiveScene;
  }

  /**
   * @brief シーンの破棄
   * @tparam T 対象のScene継承の型
   */
  template <typename T>
    requires std::is_base_of<Scene, T>::value
  void UnloadScene() {
    scenes_.erase(std::remove_if(scenes_.begin(), scenes_.end(),
                                 [](const std::shared_ptr<Scene>& scene) {
                                   return std::dynamic_pointer_cast<T>(scene) !=
                                          nullptr;
                                 }),
                  scenes_.end());
  }

  void Update() {
    for (auto& scene : scenes_) {
      scene->Update();
    }
  }

  void Render() {
    for (auto& scene : scenes_) {
      scene->Render();
    }
  }

  /**
   * @brief シーンの一覧を取得する
   * @return シーン配列
   */
  const std::vector<std::shared_ptr<Scene>>& GetScenes() const {
    return scenes_;
  }
};
