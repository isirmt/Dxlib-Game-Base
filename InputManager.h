#pragma once
#include <memory>

#include "IKeyboardProvider.h"
#include "IMouseProvider.h"
#include "Singleton.h"

/**
 * @brief インプットシステムの管理
 */
class InputManager : public Singleton<InputManager> {
 public:
  /**
   * @brief プロバイダーを設定する
   * @param mouse マウス判定プロバイダー
   * @param keyboard キーボード判定プロバイダー
   */
  void Initialize(std::shared_ptr<IMouseProvider> mouse,
                  std::shared_ptr<IKeyboardProvider> keyboard) {
    mouseProvider = mouse;
    keyboardProvider = keyboard;
  }

  /**
   * @brief マウスのプロバイダーを取得する
   * @return マウスのプロバイダー
   */
  std::shared_ptr<IMouseProvider> GetMouseProvider() const {
    return mouseProvider;
  }
  /**
   * @brief キーボードのプロバイダーを取得する
   * @return キーボードのプロバイダー
   */
  std::shared_ptr<IKeyboardProvider> GetKeyboardProvider() const {
    return keyboardProvider;
  }

 private:
  std::shared_ptr<IMouseProvider> mouseProvider;
  std::shared_ptr<IKeyboardProvider> keyboardProvider;
};
