#pragma once
#include <memory>
#include <vector>

#include "Scene.h"

/**
 * @brief �V�[���Ǘ�
 */
class SceneManager {
 public:
  SceneManager() = default;

  /**
   * @brief �V�[���ύX
   * @param newScene �C���X�^���X
   */
  void ChangeScene(std::shared_ptr<Scene> newScene) {
    scenes_.clear();
    newScene->SetAdditive(false);
    scenes_.push_back(newScene);
    newScene->Start();
  }
  /**
   * @brief �ǉ��V�[���̐ݒ�
   * @param additiveScene �C���X�^���X
   */
  void AdditiveScene(std::shared_ptr<Scene> additiveScene) {
    additiveScene->SetAdditive(true);
    scenes_.push_back(additiveScene);
    additiveScene->Start();
  }

  /**
   * @brief �V�[���̔j��
   * @param scene �Ώۂ̃V�[��
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
   * @brief �V�[���̈ꗗ���擾����
   * @return �V�[���z��
   */
  const std::vector<std::shared_ptr<Scene>>& GetScenes() const {
    return scenes_;
  }

 private:
  std::vector<std::shared_ptr<Scene>> scenes_;
};
