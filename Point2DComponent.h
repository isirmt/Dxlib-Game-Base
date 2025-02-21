#pragma once
#include "Component.h"

class Point2DComponent : public Component {
 public:
  /**
   * @brief �`��F
   */
  unsigned int color;

  /**
   * @brief �_��`�悷��
   * @param _color DxLib�ɂ��GetColor�̕Ԃ�l
   */
  Point2DComponent(unsigned int _color) : color(_color) {};

  void Render() override;
};
