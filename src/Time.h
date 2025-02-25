#pragma once
#include <chrono>
#include <thread>

#include "DxLib.h"
#include "Singleton.h"

/**
 * @brief 時間管理
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
   * @brief フレーム更新の遅延を取得数r
   * @return 遅延時間
   */
  float GetDeltaTime() const { return deltaTime; }

  /**
   * @brief 目標FPSの設定
   * @param fps FPS
   */
  void SetTargetFPS(float fps) { targetFPS = fps; }
  /**
   * @brief FPSを無制限にするか
   * @param flag フラグ
   */
  void SetunlimitedFPS(bool flag) { unlimitedFPS = flag; }

  /**
   * @brief フレーム遅延を計算する(毎ループに1回読みだす必要あり)
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
