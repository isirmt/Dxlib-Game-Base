#pragma once
#include "Component.h"

class Rect2DComponent : public Component {
 public:
  float sx, sy; // 長方形のサイズ
  unsigned int color; // DxLibによる色指定

  /**
   * @brief 長方形を描画する
   * @param _sx 幅
   * @param _sy 高さ
   * @param _color DxLibによる色指定
   */
  Rect2DComponent(float _sx, float _sy, unsigned int _color)
      : sx(_sx), sy(_sy), color(_color) {}

  void Render() override;
};
