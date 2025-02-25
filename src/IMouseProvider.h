#pragma once

/**
 * @brief マウス判定のインターフェース
 */
class IMouseProvider {
 public:
  virtual ~IMouseProvider() = default;

  /**
   * @brief マウス座標を取得する
   * @param x X座標参照
   * @param y Y座標参照
   */
  virtual void GetMousePosition(int& x, int& y) = 0;

  /**
   * @brief マウスのボタンが押されているか
   * @param buttonFlag ボタンのコード
   * @return TRUE: 押されている
   */
  virtual bool IsMouseButtonDown(int buttonFlag) = 0;
};
