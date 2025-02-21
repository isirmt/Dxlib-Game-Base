#pragma once

/**
 * @brief 画面座標を特定の座標へ変換するインターフェース
 */
class IMouseCoordinateConverter {
 public:
  virtual ~IMouseCoordinateConverter() = default;

  /**
   * @brief 座標変換の実行
   * @param screenX 画面座標X
   * @param screenY 画面座標Y
   * @param outX 変換後のX参照
   * @param outY 変換後のY参照
   */
  virtual void Convert(int screenX, int screenY, int& outX, int& outY) = 0;
};
