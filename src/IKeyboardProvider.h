#pragma once

/**
 * @brief キーボード判定のインターフェース
 */
class IKeyboardProvider {
 public:
  virtual ~IKeyboardProvider() = default;
  /**
   * @brief 特定のキーコードが押されているか
   * @param keyCode キーコード
   * @return TRUE: 押されている
   */
  virtual bool IsKeyDown(int keyCode) = 0;
};
