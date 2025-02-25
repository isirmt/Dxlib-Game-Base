#pragma once
#include <memory>
#include <vector>

#include "Scene.h"

/**
 * @brief シーン管理
 */
class SceneManager {
 public:
  SceneManager() = default;

  /**
   * @brief シーン変更
   * @param newScene インスタンス
   */
  void ChangeScene(std::shared_ptr<Scene> newScene) {
    scenes_.clear();
    newScene->SetAdditive(false);
    scenes_.push_back(newScene);
    newScene->Start();
  }
  /**
   * @brief 追加シーンの設定
   * @param additiveScene インスタンス
   */
  void AdditiveScene(std::shared_ptr<Scene> additiveScene) {
    additiveScene->SetAdditive(true);
    scenes_.push_back(additiveScene);
    additiveScene->Start();
  }

  /**
   * @brief シーンの破棄
   * @param scene 対象のシーン
   */
  void UnloadScene(std::shared_ptr<Scene> scene) {
    scenes_.erase(std::remove(scenes_.begin(), scenes_.end(), scene),
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

 private:
  std::vector<std::shared_ptr<Scene>> scenes_;
};
