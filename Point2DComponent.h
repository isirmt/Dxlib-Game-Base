#pragma once
#include "Component.h"

class Point2DComponent : public Component {
 public:
  /**
   * @brief 描画色
   */
  unsigned int color;

  /**
   * @brief 点を描画する
   * @param _color DxLibによるGetColorの返り値
   */
  Point2DComponent(unsigned int _color) : color(_color) {};

  void Render() override;
};
