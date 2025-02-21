#pragma once
#include "DxLib.h"

/**
 * @brief キャンバスを管理する
 */
class RenderTarget {
 public:
  /**
   * @brief 任意のレイヤー値
   */
  int layer;
  /**
   * @brief ライブラリによって割り当てられたハンドル
   */
  int handle;
  int width, height; // スクリーンサイズ

  /**
   * @brief キャンバスの作成
   * @param _layer 任意のレイヤー値
   * @param _width 幅
   * @param _height 高さ
   */
  RenderTarget(int _layer, int _width, int _height)
      : layer(_layer), width(_width), height(_height) {
    handle = MakeScreen(width, height, true);
  }

  ~RenderTarget() { DeleteGraph(handle); }
};
