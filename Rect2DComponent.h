#pragma once
#include "Component.h"

class Rect2DComponent : public Component {
 public:
  float sx, sy; // �����`�̃T�C�Y
  unsigned int color; // DxLib�ɂ��F�w��

  /**
   * @brief �����`��`�悷��
   * @param _sx ��
   * @param _sy ����
   * @param _color DxLib�ɂ��F�w��
   */
  Rect2DComponent(float _sx, float _sy, unsigned int _color)
      : sx(_sx), sy(_sy), color(_color) {}

  void Render() override;
};
