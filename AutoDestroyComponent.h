#pragma once
#include "Component.h"

class AutoDestroyComponent : public Component {
 public:
  float seconds;  // �ݒ�b��
  float remain;   // �c�莞��

  /**
   * @brief �w�肵���b���̌�C������Destroy�����s����
   * @param _seconds �b��
   */
  AutoDestroyComponent(float _seconds) : seconds(_seconds), remain(_seconds) {}

  void Update() override;
};
