#pragma once
#include "Component.h"

/**
 * @brief ボタンやドラッグ，衝突判定に利用可能な長方形判定コンポーネント
 */
class ColliderComponent : public Component {
 public:
  /**
   * @brief 判定の大きさ
   */
  float width, height;

  /**
   * @brief 長方形判定のサイズを指定する
   * @param w 幅
   * @param h 高さ
   */
  ColliderComponent(float w, float h) : width(w), height(h) {}

  /**
   * @brief 特定の「キャンバス座標」がオブジェクトの範囲に入っているか判定する
   * @param x キャンバスX座標
   * @param y キャンバスY座標
   * @return TRUE: 入っている, FALSE: 入っていない
   */
  bool Contains(float x, float y);
};
