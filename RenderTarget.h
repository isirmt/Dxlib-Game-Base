#pragma once
#include "DxLib.h"

class RenderTarget {
 public:
  int layer;
  int handle;  // DX���C�u�����̃I�t�X�N���[���n���h��
  int width, height;

  RenderTarget(int _layer, int _width, int _height)
      : layer(_layer), width(_width), height(_height) {
    handle = MakeScreen(width, height, true);
  }

  ~RenderTarget() { DeleteGraph(handle); }
};
