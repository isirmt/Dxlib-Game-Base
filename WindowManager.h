#pragma once

/**
 * @brief ウインドウ情報管理
 */
class WindowManager {
 public:
  /**
   * @brief ウインドウ設計サイズ
   */
  int designWidth, designHeight;
  /**
   * @brief ウインドウ実寸
   */
  int windowWidth, windowHeight;
  /**
   * @brief ウインドウの設計サイズからの倍率
   */
  float scaleX, scaleY;

  /**
   * @brief ウインドウの初期サイズの設定
   * @param dWidth 
   * @param dHeight 
   */
  WindowManager(int dWidth, int dHeight)
      : designWidth(dWidth),
        designHeight(dHeight),
        windowWidth(dWidth),
        windowHeight(dHeight),
        scaleX(1.0f),
        scaleY(1.0f) {}

  /**
   * @brief ウインドウのサイズ倍率を再計算する
   * @param newWidth 
   * @param newHeight 
   */
  void UpdateWindowSize(int newWidth, int newHeight) {
    windowWidth = newWidth;
    windowHeight = newHeight;
    scaleX = static_cast<float>(designWidth) / newWidth;
    scaleY = static_cast<float>(designHeight) / newHeight;
  }

  /**
   * @brief ウインドウの倍率からスクリーン座標から画面座標に変換する
   * @param windowX 
   * @param windowY 
   * @param gameX 
   * @param gameY 
   */
  void ConvertMousePosition(int windowX, int windowY, int& gameX, int& gameY) {
    gameX = static_cast<int>(windowX * scaleX);
    gameY = static_cast<int>(windowY * scaleY);
  }
};
