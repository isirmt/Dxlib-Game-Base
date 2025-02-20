#pragma once
#include "Component.h"

class AutoDestroyComponent : public Component {
 public:
  float seconds;  // 設定秒数
  float remain;   // 残り時間

  /**
   * @brief 指定した秒数の後，自動でDestroyを実行する
   * @param _seconds 秒数
   */
  AutoDestroyComponent(float _seconds) : seconds(_seconds), remain(_seconds) {}

  void Update() override;
};
