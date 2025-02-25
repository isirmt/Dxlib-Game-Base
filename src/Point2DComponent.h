#pragma once
#include "Component.h"

class Point2DComponent : public Component {
 public:
  /**
   * @brief •`‰æF
   */
  unsigned int color;

  /**
   * @brief “_‚ğ•`‰æ‚·‚é
   * @param _color DxLib‚É‚æ‚éGetColor‚Ì•Ô‚è’l
   */
  Point2DComponent(unsigned int _color) : color(_color) {};

  void Render() override;
};
