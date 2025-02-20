#pragma once
#include <memory>

#include "IKeyboardProvider.h"
#include "IMouseProvider.h"
#include "Singleton.h"

class InputManager : public Singleton<InputManager> {
 public:
  void Initialize(std::shared_ptr<IMouseProvider> mouse,
                  std::shared_ptr<IKeyboardProvider> keyboard) {
    mouseProvider = mouse;
    keyboardProvider = keyboard;
  }

  std::shared_ptr<IMouseProvider> GetMouseProvider() const {
    return mouseProvider;
  }
  std::shared_ptr<IKeyboardProvider> GetKeyboardProvider() const {
    return keyboardProvider;
  }

 private:
  std::shared_ptr<IMouseProvider> mouseProvider;
  std::shared_ptr<IKeyboardProvider> keyboardProvider;
};
