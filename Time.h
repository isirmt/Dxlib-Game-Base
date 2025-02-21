#pragma once
#include <chrono>
#include <thread>

#include "DxLib.h"
#include "Singleton.h"

/**
 * @brief ���ԊǗ�
 */
class Time : public Singleton<Time> {
  friend class Singleton<Time>;
  static float deltaTime;
  static float targetFPS;
  static bool unlimitedFPS;

 protected:
  Time() = default;

 public:
  /**
   * @brief �t���[���X�V�̒x�����擾��r
   * @return �x������
   */
  float GetDeltaTime() const { return deltaTime; }

  /**
   * @brief �ڕWFPS�̐ݒ�
   * @param fps FPS
   */
  void SetTargetFPS(float fps) { targetFPS = fps; }
  /**
   * @brief FPS�𖳐����ɂ��邩
   * @param flag �t���O
   */
  void SetunlimitedFPS(bool flag) { unlimitedFPS = flag; }

  /**
   * @brief �t���[���x�����v�Z����(�����[�v��1��ǂ݂����K�v����)
   */
  void Update() {
    using namespace std::chrono;
    static auto lastTime = high_resolution_clock::now();
    auto currentTime = high_resolution_clock::now();
    duration<float> elapsed = currentTime - lastTime;
    deltaTime = elapsed.count();
    lastTime = currentTime;

    if (!unlimitedFPS) {
      float frameTime = 1.f / targetFPS;
      if (deltaTime < frameTime) {
        std::this_thread::sleep_for(duration<float>(frameTime - deltaTime));
        deltaTime = frameTime;
      }
    }
  }
};
